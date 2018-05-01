#include "blockcanvas.h"

#include <QPainter>
#include <QMimeData>
#include <QJsonDocument>
#include <QGraphicsScene>
#include <app/core/blockmanager.h>

BlockCanvas::BlockCanvas(QGraphicsWidget* parent): ScrollArea(parent)
{
    m_blockManager = new BlockManager;

    this->setGrooveColor(QColor(Qt::transparent));
    this->setHandleColor(QColor("#4c4c4c"));
    this->setAcceptDrops(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);
}

BlockCanvas::~BlockCanvas()
{
    delete m_blockManager;
}

void BlockCanvas::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->save();
    painter->setPen(QPen{QColor{"#8c8c8c"}, 3});
    painter->setOpacity(0.7);

    if(m_drawLine) {
        QPainterPath path;
        QPointF p1 = m_portStartPoint;
        QPointF p2 = m_portEndPoint;

        path.moveTo(p1);
        double startX = qMin(p1.x(), p2.x());
        const QPointF c1{startX + qAbs((p1.x() - p2.x()) / 2.), p1.y()};
        const QPointF c2{startX + qAbs((p1.x() - p2.x()) / 2.), p2.y()};

        path.cubicTo(c1, c2, p2);
        painter->drawPath(path);
    }

    if(m_dragOver) {
        painter->setPen(QColor(Qt::transparent));
        painter->setBrush(QColor("#efefef"));
        painter->drawRect(this->boundingRect());
    }

    painter->restore();
}

void BlockCanvas::dragEnterEvent(QGraphicsSceneDragDropEvent* e)
{
    if(e->mimeData()->hasFormat(BlockManager::blockMimeType())) {
        m_dragOver = true;
        e->setAccepted(true);
        this->update();
    }

    else
        e->setAccepted(false);
}

void BlockCanvas::dragLeaveEvent(QGraphicsSceneDragDropEvent* e)
{
    Q_UNUSED(e);
    m_dragOver = false;
    this->update();
}

void BlockCanvas::dropEvent(QGraphicsSceneDragDropEvent* e)
{
    if(m_disableDrop)
        return;

    m_dragOver = false;
    if(e->mimeData()->hasFormat(BlockManager::blockMimeType())) {
        QByteArray rawData{e->mimeData()->data(BlockManager::blockMimeType())};
        QDataStream data{&rawData, QIODevice::ReadOnly};
        QPoint hotspot;
        QByteArray jsonData;
        data >> hotspot;
        data >> jsonData;

        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        auto block = BlockManager::blockFromJson(doc.object(), this->container());
        m_blockManager->addBlock(block);

        block->view()->setCopyable(false);
        block->view()->setFlag(QGraphicsItem::ItemIsSelectable);
        block->view()->setFlag(QGraphicsItem::ItemIsMovable);

        block->view()->setPos(e->pos() - QPointF(hotspot));
        block->view()->setOutputVisible(false, false);
        block->view()->setInputsVisible(false, false);
        block->view()->setOutputVisible(true);
        block->view()->setInputsVisible(true);
    }

    this->update();
}

void BlockCanvas::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    BlockPortView* portView = this->portViewAtPos(e->pos());

    if(portView == nullptr) {
        QGraphicsWidget::mousePressEvent(e);
        return;
    }

    m_portOrigStartPoint = e->pos();
    m_portStartPoint = portView->mapToItem(
                           this, QPointF(0, portView->size().height() / 2.));
    m_drawLine = true;
}

void BlockCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent* e)
{
    m_portEndPoint = e->pos();
    this->update();
    QGraphicsWidget::mouseMoveEvent(e);
}

void BlockCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
    // TODO print warning
    // TODO check cycles
    BlockPortView* toPortView = this->portViewAtPos(e->pos());

    if(!m_drawLine || toPortView == nullptr) {
        m_drawLine = false;
        m_portStartPoint = QPointF(-1, -1);;
        this->update();
        QGraphicsWidget::mouseReleaseEvent(e);
        return;
    }

    m_drawLine = false;
    m_portStartPoint = QPointF(-1, -1);;

    // check if it is relesed over input port
    if(toPortView->portData()->isOutput()) {
        this->update();
        return;
    }

    BlockPortView* outPortView = this->portViewAtPos(m_portOrigStartPoint);
    Block* fromBlock = m_blockManager->block(outPortView->portData()->blockId());
    Block* toBlock = m_blockManager->block(toPortView->portData()->blockId());
    PortIdentifier toPortId = toBlock->inputPorts().indexOf(toPortView->portData());

    if(outPortView->portData()->type() != toPortView->portData()->type()) {
        this->update();
        return;
    }

    auto join = new Join{fromBlock->id(), 0, toBlock->id(), toPortId, this->container()};
    join->setBlockManager(m_blockManager);
    m_blockManager->addJoin(join);
    outPortView->animateHide();
    toPortView->animateHide();
    join->view()->adjustJoin();
    this->update();
}

BlockPortView* BlockCanvas::portViewAtPos(QPointF pos) const
{
    QList<BlockPortView*> portViews;
    for(auto singlePortView: this->scene()->items(pos + this->pos())) {
        BlockPortView* castedPortView = dynamic_cast<BlockPortView*>(singlePortView);
        if(castedPortView != nullptr)
            portViews.append(castedPortView);
    }

    if(!portViews.length())
        return nullptr;
    return portViews.at(0);
}

bool BlockCanvas::schemeValidity() const
{
    bool valid = true;
    for(auto block: m_blockManager->blocks().values())
        valid = valid && block->validInputs();

    return valid;
}

QList<Identifier> BlockCanvas::blockComputeOrder()
{
    QList<Identifier> computedBlocks;
    while(computedBlocks.size() < m_blockManager->blocks().values().length()) {
        for(auto block: m_blockManager->blocks().values()) {
            if(computedBlocks.contains(block->id()))
                continue;
            const QSet<Identifier> blockOuts = m_blockManager->blockBlocksInputs(block->id());
            bool blockEvaluable = blockOuts.isEmpty() ||
                                  (blockOuts - computedBlocks.toSet()).isEmpty();
            if(blockEvaluable)
                computedBlocks.append(block->id());
        }
    }

    return computedBlocks;
}


void BlockCanvas::evaluateBlock(Identifier blockId)
{
    Block* block = m_blockManager->block(blockId);
    MappedDataValues res = block->evaluate(block->view()->values());
    QList<QPair<Identifier, Identifier> > blocksTopropagate =
            m_blockManager->blockOutputs(block->id());

    block->outputPort()->setValue(res);
    for(auto outData: blocksTopropagate) {
        m_blockManager->blocks()[outData.first]->inputPorts()
                .at(static_cast<int>(outData.second))->setValue(res);
    }
}

void BlockCanvas::evaluate()
{
    // TODO validate
    // check if ports are valid
    qDebug() << this->schemeValidity();
    if(!this->schemeValidity())
        return;
    // compute available blocks
    for(Identifier blockId: this->blockComputeOrder())
        this->evaluateBlock(blockId);
}

void BlockCanvas::debug()
{
    // TODO validate
    QList<Identifier> computeOrder = this->blockComputeOrder();
    if(m_debugIteration >= computeOrder.length()) {
        this->stopDebug();
        return;
    }

    if(m_debugIteration == 0)
        this->scene()->clearSelection();
    m_blockManager->setDisableDelete(true);
    this->setDisableDrop(true);

    Block* block = m_blockManager->block(computeOrder.at(m_debugIteration));
    block->view()->setSelected(true);

    if(m_debugIteration > 0)
        m_blockManager->block(computeOrder.at(m_debugIteration - 1))->view()->setSelected(false);
    this->evaluateBlock(block->id());

    m_debugIteration++;
}

void BlockCanvas::stopDebug()
{
    m_debugIteration = 0;
    m_blockManager->setDisableDelete(false);
    this->scene()->clearSelection();
    this->setDisableDrop(false);
}

void BlockCanvas::setDisableDrop(bool v)
{
    m_disableDrop = v;
}

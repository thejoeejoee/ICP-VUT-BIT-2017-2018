#include "blockcanvas.h"

#include <QPainter>
#include <QMimeData>
#include <QJsonDocument>
#include <QGraphicsScene>
#include <app/core/blockmanager.h>

BlockCanvas::BlockCanvas(QGraphicsWidget* parent): ScrollArea(parent)
{
    m_blockManager = new BlockManager;

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
    painter->setPen(QPen{QColor{"#4c4c4c"}, 3});
    if(m_portStartPoint != QPointF(-1, -1))
        painter->drawLine(m_portStartPoint, m_portEndPoint);
    painter->restore();
}

void BlockCanvas::dragEnterEvent(QGraphicsSceneDragDropEvent* e)
{
    if(e->mimeData()->hasFormat(BlockManager::blockMimeType())) {
        m_dragOver = true;
        e->setAccepted(true);
        // TODO aimation?
        this->update();
    }

    else
        e->setAccepted(false);
}

void BlockCanvas::dragLeaveEvent(QGraphicsSceneDragDropEvent* e)
{
    Q_UNUSED(e);
    // TODO animation?
    m_dragOver = false;
    this->update();
}

void BlockCanvas::dropEvent(QGraphicsSceneDragDropEvent* e)
{
    // TODO animation?
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
        block->view()->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

        block->view()->setPos(e->pos() - QPointF(hotspot));
        block->view()->setOutputVisible(false, false);
        block->view()->setInputsVisible(false, false);
        block->view()->setOutputVisible(true);
        block->view()->setInputsVisible(true);
    }
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
    // TODO check types
    BlockPortView* toPortView = this->portViewAtPos(e->pos());
    if(m_portStartPoint == QPointF(-1, -1) || toPortView == nullptr) {
        this->update();
        QGraphicsWidget::mouseReleaseEvent(e);
        return;
    }

    m_portStartPoint = QPointF(-1, -1);
    m_drawLine = false;

    // check if it is relesed over input port
    if(toPortView->data()->isOutput()) {
        this->update();
        return;
    }

    BlockPortView* outPortView = this->portViewAtPos(m_portOrigStartPoint);
    Block* fromBlock = m_blockManager->block(outPortView->data()->blockId());
    Block* toBlock = m_blockManager->block(toPortView->data()->blockId());
    PortIdentifier toPortId = toBlock->inputPorts().indexOf(toPortView->data());

    auto join = new Join{fromBlock->id(), 0, toBlock->id(), toPortId, this};
    m_blockManager->addJoin(join);
    outPortView->animateHide();
    toPortView->animateHide();

    auto reconnectJoin = [this, outPortView, toPortView, join]{
        QPointF start = outPortView->mapToItem(this, QPointF(
                                                   0,
                                                   outPortView->size().height() / 2.));
        QPointF end = toPortView->mapToItem(this, QPointF(
                                                toPortView->size().width(),
                                                toPortView->size().height() / 2.));
        join->view()->setLine(QLineF(start, end));
    };

    reconnectJoin();
    connect(fromBlock->view(), &BlockView::geometryChanged, reconnectJoin);
    connect(toBlock->view(), &BlockView::geometryChanged, reconnectJoin);

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

#include "joinview.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QPainter>
#include <app/core/block.h>
#include <app/ui/blockview.h>
#include <app/core/blockmanager.h>

JoinView::JoinView(Identifier dataId, QGraphicsItem* parent)
    : QObject{}, QGraphicsLineItem(parent)
{
    m_dataId = dataId;
    m_pen = QPen{QColor{"#8c8c8c"}, 3};
    this->setPen(m_pen);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(ItemIsFocusable);
}

void JoinView::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Delete) {
        for(auto item: this->scene()->selectedItems()) {
            auto blockView = dynamic_cast<BlockView*>(item);
            auto joinView = dynamic_cast<JoinView*>(item);

            if(blockView != nullptr)
                emit blockView->deleteRequest(blockView->blockData()->id());
            else if(joinView != nullptr)
                emit joinView->deleteRequest(joinView->dataId());
        }
    }

    QGraphicsLineItem::keyPressEvent(event);
}

QVariant JoinView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if(change == QGraphicsItem::ItemSelectedChange) {
        if(value == true) {
            this->setFocus();
            m_pen.setColor(QColor{"#0f81bc"});
        }
        else
            m_pen.setColor(QColor{"#4c4c4c"});
        this->setPen(m_pen);
        this->update();
    }

    return QGraphicsLineItem::itemChange(change, value);
}

void JoinView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(this->pen());
    painter->drawPath(this->shape());
}

QPainterPath JoinView::shape() const
{
    QPainterPath path;
    QPointF p1 = this->line().p1();
    QPointF p2 = this->line().p2();

    path.moveTo(p1);
    double startX = qMin(p1.x(), p2.x());
    const QPointF c1{startX + qAbs((p1.x() - p2.x()) / 2.), p1.y()};
    const QPointF c2{startX + qAbs((p1.x() - p2.x()) / 2.), p2.y()};

    path.cubicTo(c1, c2, p2);

    return path;
}

Identifier JoinView::dataId() const
{
    return m_dataId;
}

void JoinView::setBlockManager(BlockManager* m)
{
    m_blockManager = m;
}

void JoinView::adjustJoin()
{
    if(m_blockManager == nullptr)
        return;

    Join* data = m_blockManager->join(m_dataId);
    BlockPortView* fromPortView = m_blockManager->block(data->fromBlock())->outputPort()->view();
    BlockPortView* toPortView = m_blockManager->block(data->toBlock())->inputPorts()
                                .at(data->toPort())->view();

    QPointF start = fromPortView->mapToItem(this->parentItem(), QPointF(
                                               0,
                                               fromPortView->size().height() / 2.));
    QPointF end = toPortView->mapToItem(this->parentItem(), QPointF(
                                            toPortView->size().width(),
                                            toPortView->size().height() / 2.));
    this->setLine(QLineF(start, end));
    this->update();
}

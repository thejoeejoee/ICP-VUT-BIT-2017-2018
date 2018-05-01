#include "joinview.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

JoinView::JoinView(QGraphicsItem* parent): QGraphicsLineItem(parent)
{
    m_pen = QPen{QColor{"#4c4c4c"}, 3};
    this->setPen(m_pen);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

QVariant JoinView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if(change == QGraphicsItem::ItemSelectedChange) {
        if(value == true)
            m_pen.setColor(QColor{"#0f81bc"});
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
    painter->drawLine(this->line());
}

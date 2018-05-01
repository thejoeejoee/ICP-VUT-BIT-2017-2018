#include "clickable.h"

#include <QPainter>

Clickable::Clickable(QGraphicsItem* parent): QGraphicsWidget (parent)
{
    this->setAcceptHoverEvents(true);
}

void Clickable::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    if(m_hovered) {
        painter->setOpacity(0.4);
        painter->setPen(QColor(Qt::transparent));
        painter->setBrush(QColor(Qt::white));
        painter->drawRect(this->boundingRect());
    }
    painter->restore();
}

void Clickable::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    emit this->clicked();
}

void Clickable::hoverEnterEvent(QGraphicsSceneHoverEvent* e)
{
    m_hovered = true;
    this->update();
}

void Clickable::hoverLeaveEvent(QGraphicsSceneHoverEvent* e)
{
    m_hovered = false;
    this->update();
}

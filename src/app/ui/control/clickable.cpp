#include "clickable.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

Clickable::Clickable(QGraphicsItem* parent): QGraphicsWidget (parent)
{
    this->setAcceptHoverEvents(true);
}

void Clickable::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget);
    painter->setClipRect(option->exposedRect);

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
    Q_UNUSED(e);

    emit this->clicked();
}

void Clickable::hoverEnterEvent(QGraphicsSceneHoverEvent* e)
{
    Q_UNUSED(e);

    m_hovered = true;
    this->update();
}

void Clickable::hoverLeaveEvent(QGraphicsSceneHoverEvent* e)
{
    Q_UNUSED(e);

    m_hovered = false;
    this->update();
}

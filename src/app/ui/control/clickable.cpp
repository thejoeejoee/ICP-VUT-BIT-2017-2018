#include "clickable.h"

Clickable::Clickable(QGraphicsItem* parent): QGraphicsWidget (parent) {}

void Clickable::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    emit this->clicked();
}

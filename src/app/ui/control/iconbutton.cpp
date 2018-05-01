#include "iconbutton.h"

#include <QPainter>

IconButton::IconButton(QGraphicsItem* parent): Clickable (parent)
{

}

void IconButton::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->save();
    painter->setBrush(QColor(Qt::blue));
    painter->drawRect(this->boundingRect());
    painter->restore();
}

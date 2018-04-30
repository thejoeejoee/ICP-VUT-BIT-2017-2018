#include "joinview.h"

#include <QPen>

JoinView::JoinView(QGraphicsItem* parent): QGraphicsLineItem(parent)
{
    this->setPen(QPen{QColor{"#4c4c4c"}, 3});
}

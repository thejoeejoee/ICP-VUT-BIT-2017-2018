#include "blockview.h"

#include <QPainter>

BlockView::BlockView(QGraphicsItem* parent) : QGraphicsWidget(parent)
{
    this->setMinimumSize(50, 50);
}

void BlockView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setBrush(QColor(Qt::blue));
    painter->drawRect(this->rect());
    painter->restore();
}

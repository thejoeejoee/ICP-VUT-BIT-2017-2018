#include "blockview.h"

#include <QPainter>

BlockView::BlockView(Block* block, QGraphicsItem* parent) : QGraphicsWidget(parent)
{
    m_data = block;
    this->setMinimumSize(50, 50);
}

void BlockView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setBrush(QColor(Qt::blue));
    painter->drawRect(this->rect());
    painter->restore();
}

Block* BlockView::blockData() const
{
    return m_data;
}

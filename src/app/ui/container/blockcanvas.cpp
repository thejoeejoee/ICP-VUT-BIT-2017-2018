#include "blockcanvas.h"

#include <QPainter>

BlockCanvas::BlockCanvas(QGraphicsWidget* parent): ScrollArea(parent)
{

}

void BlockCanvas::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->save();

    painter->restore();
}

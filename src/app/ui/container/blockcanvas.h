#ifndef BLOCKCANVAS_H
#define BLOCKCANVAS_H

#include "scrollarea.h"



class BlockCanvas : public ScrollArea
{
    public:
        explicit BlockCanvas(QGraphicsWidget* parent = nullptr);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // BLOCKCANVAS_H

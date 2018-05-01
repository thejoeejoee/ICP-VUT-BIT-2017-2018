#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include "clickable.h"


class IconButton : public Clickable
{
        Q_OBJECT
    public:
        IconButton(QGraphicsItem* parent = nullptr);

        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget = nullptr) override;
};

#endif // ICONBUTTON_H

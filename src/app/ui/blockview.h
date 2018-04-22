#ifndef BLOCKVIEW_H
#define BLOCKVIEW_H

#include <QGraphicsWidget>

class BlockView : public QGraphicsWidget
{
        Q_OBJECT
    public:
        explicit BlockView(QGraphicsItem *parent = nullptr);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // BLOCKVIEW_H

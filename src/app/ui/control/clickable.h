#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <QGraphicsWidget>


class Clickable : public QGraphicsWidget
{
        Q_OBJECT
    public:
        Clickable(QGraphicsItem* parent = nullptr);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* e) override;

    signals:
        void clicked();
};

#endif // CLICKABLE_H

#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <QGraphicsWidget>


class Clickable : public QGraphicsWidget
{
        Q_OBJECT
    private:
        bool m_hovered = false;

    public:
        Clickable(QGraphicsItem* parent = nullptr);

        void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget = nullptr) override;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* e) override;

        void hoverEnterEvent(QGraphicsSceneHoverEvent* e) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* e) override;

    signals:
        void clicked();
};

#endif // CLICKABLE_H

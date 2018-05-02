#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <QGraphicsWidget>


/**
 * Base widget to clickable items.
 */
class Clickable : public QGraphicsWidget {
    Q_OBJECT
    private:
        bool m_hovered = false;

    public:
        explicit Clickable(QGraphicsItem* parent = nullptr);
        /**
         * Paints widget via painter.
         * @param painter painter
         * @param option style
         * @param widget qt parent widget
         */
        void paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget) override;

    protected:
        /**
         * On mouse click.
         * @param e click event
         */
        void mousePressEvent(QGraphicsSceneMouseEvent* e) override;

        /**
         * On mouse hover enter.
         * @param e enter event
         */
        void hoverEnterEvent(QGraphicsSceneHoverEvent* e) override;
        /**
         * On mouse hover leavel.
         * @param e enter event
         */
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* e) override;

    signals:
        /**
         * On widget click.
         */
        void clicked();
};

#endif // CLICKABLE_H

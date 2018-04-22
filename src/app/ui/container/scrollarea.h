#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QGraphicsWidget>
#include "../control/scrollbar.h"

// TODO delete
class Rect: public QGraphicsWidget
{
    Q_OBJECT
    public:
        explicit Rect(QGraphicsWidget* parent = nullptr): QGraphicsWidget(parent) {}

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget =nullptr) override;
};


class ScrollArea: public QGraphicsWidget
{
    Q_OBJECT
    private:
        QGraphicsWidget* m_container;
        ScrollBar* m_verticalScrollBar;
        ScrollBar* m_horizontalScrollBar;

    public:
        explicit ScrollArea(QGraphicsWidget *parent = nullptr);

        QGraphicsWidget* container() const;

    private slots:
        void manageScrollbarsVisibility();
        void repositionVerticalContent(qreal relPos);
        void repositionHorizontalContent(qreal relPos);

};

#endif // SCROLLAREA_H

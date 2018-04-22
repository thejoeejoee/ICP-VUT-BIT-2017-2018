#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsWidget>
#include "../control/scrollbar.h"

class ScrollArea: public QGraphicsWidget
{
    Q_OBJECT
    private:
        QGraphicsWidget* m_container;
        ScrollBar* m_verticalScrollBar;
        ScrollBar* m_horizontalScrollBar;

    public:
        explicit ScrollArea(QGraphicsWidget *parent = nullptr);

    protected:
        void wheelEvent(QGraphicsSceneWheelEvent* e) override;

    public:
        QGraphicsWidget* container() const;

    private slots:
        void manageScrollbarsVisibility();
        void repositionVerticalContent(qreal relPos);
        void repositionHorizontalContent(qreal relPos);

};

#endif // SCROLLAREA_H

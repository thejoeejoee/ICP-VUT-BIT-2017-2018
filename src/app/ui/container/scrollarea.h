#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsWidget>
#include "../control/scrollbar.h"


class StretchContainer: public QGraphicsWidget {
        Q_OBJECT
    public:
        StretchContainer(QGraphicsItem* parent = nullptr);

    protected:
        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

    private slots:
        void resizeToChildren();
};

class ScrollArea: public QGraphicsWidget
{
    Q_OBJECT
    private:
        StretchContainer* m_container;
        ScrollBar* m_verticalScrollBar;
        ScrollBar* m_horizontalScrollBar;

    public:
        ScrollArea(QGraphicsItem *parent = nullptr);

    protected:
        void wheelEvent(QGraphicsSceneWheelEvent* e) override;

    public:
        StretchContainer* container() const;

    private slots:
        void manageScrollbarsVisibility();
        void repositionVerticalContent(qreal relPos);
        void repositionHorizontalContent(qreal relPos);

    public slots:
        void setHandleColor(const QColor& color);
        void setGrooveColor(const QColor& color);
};

#endif // SCROLLAREA_H

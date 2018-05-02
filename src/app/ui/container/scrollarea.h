#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsWidget>
#include "../control/scrollbar.h"

/**
 * Container to stretch parent.
 */
class StretchContainer : public QGraphicsWidget {
    Q_OBJECT
    public:
        explicit StretchContainer(QGraphicsItem* parent = nullptr);

    protected:
        /**
         * Change of value.
         * @param change change
         * @param value new value
         * @return new value
         */
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    private slots:
        /**
         * Change size to stretch all children.
         */
        void resizeToChildren();
};

/**
 * Custom scroll area.
 */
class ScrollArea : public QGraphicsWidget {
    Q_OBJECT
    private:
        StretchContainer* m_container;
        ScrollBar* m_verticalScrollBar;
        ScrollBar* m_horizontalScrollBar;

    public:
        explicit ScrollArea(QGraphicsItem* parent = nullptr);

    protected:
        /**
         * On wheel event.
         * @param e event
         */
        void wheelEvent(QGraphicsSceneWheelEvent* e) override;

    public:
        StretchContainer* container() const;

    private slots:
        void manageScrollbarsVisibility();
        void repositionVerticalContent(qreal relPos);
        void repositionHorizontalContent(qreal relPos);

    public slots:
        /**
         * Sets color for scrollbar handle.
         * @param color color to set
         */
        void setHandleColor(const QColor &color);
        /**
         * Sets color for groove handle.
         * @param color color to set
         */
        void setGrooveColor(const QColor &color);
};

#endif // SCROLLAREA_H

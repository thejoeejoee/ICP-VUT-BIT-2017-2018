#ifndef BLOCKCANVAS_H
#define BLOCKCANVAS_H

#include "scrollarea.h"
#include <app/core/blockmanager.h>


/**
 * Canvas for all placed blocks in application.
 */
class BlockCanvas : public ScrollArea {
    Q_OBJECT
    private:
        bool m_dragOver = false;
        QPointF m_portStartPoint = QPointF(-1, -1);
        QPointF m_portOrigStartPoint;
        QPointF m_portEndPoint = QPointF();
        bool m_drawLine = false;
        BlockManager* m_blockManager;
        int m_debugIteration = 0;
        bool m_disableDrop = false;

    public:
        explicit BlockCanvas(QGraphicsWidget* parent = nullptr);
        ~BlockCanvas() override;
        /**
         * Paints to canvas.
         * @param painter painter
         * @param option style
         * @param widget optional qt parent
         */
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    private:
        QList<Identifier> blockComputeOrder();

    protected:
        /**
         * Start of drag event.
         * @param e drag event
         */
        void dragEnterEvent(QGraphicsSceneDragDropEvent* e) override;
        /**
         * End of drag event.
         * @param e drag event
         */
        void dragLeaveEvent(QGraphicsSceneDragDropEvent* e) override;
        /**
         * Drop event.
         * @param e drop event
         */
        void dropEvent(QGraphicsSceneDragDropEvent* e) override;

        /**
         * Mouse click event.
         * @param e mouse event
         */
        void mousePressEvent(QGraphicsSceneMouseEvent* e) override;
        /**
         * Mouse move event.
         * @param e mouse event
         */
        void mouseMoveEvent(QGraphicsSceneMouseEvent* e) override;
        /**
         * Mouse release event.
         * @param e mouse event
         */
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;

        /**
         * Returns port view placed at given position
         * @param pos position to detect
         * @return port on position
         */
        BlockPortView* portViewAtPos(QPointF pos) const;

        /**
         * Is schema valid?
         * @return
         */
        bool schemeValidity() const;
        /**
         * Is schema cycled?
         * @return state
         */
        bool cycled() const;

    public:
        /**
         * Returns manager from block canvas.
         * @return block manager
         */
        BlockManager* manager() const;

    private slots:
        /**
         * Evaluate concrete block.
         * @param blockId concrete block identifier
         */
        void evaluateBlock(Identifier blockId);

    public slots:
        /**
         * Eval all blocks.
         */
        void evaluate();
        /**
         * Starts debug session.
         */
        void debug();
        /**
         * Stops debug session.
         */
        void stopDebug();

        /**
         * Sets flag to disable drop.
         * @param v state
         */
        void setDisableDrop(bool v);

        /**
         * Remove all blocks and joins.
         */
        void clear();

    signals:
        // TODO doc
        void debugStateChanged(bool debugging);

        /**
         * Display error of msg.
         * @param msg text
         */
        void error(const QString &msg);
        /**
         * On block added signal.
         * @param id new block identifier
         */
        void blockAdded(Identifier id);
        /**
         * On join added signal.
         * @param id new block identifier
         */
        void joinAdded(Identifier id);
        /**
         * On join deleted signal.
         */
        void joinDeleted();
        /**
         * On block deleted signal.
         */
        void blockDeleted();
};

#endif // BLOCKCANVAS_H

#ifndef BLOCKCANVAS_H
#define BLOCKCANVAS_H

#include "scrollarea.h"
#include <app/core/blockmanager.h>


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
        void dragEnterEvent(QGraphicsSceneDragDropEvent* e) override;
        void dragLeaveEvent(QGraphicsSceneDragDropEvent* e) override;
        void dropEvent(QGraphicsSceneDragDropEvent* e) override;

        void mousePressEvent(QGraphicsSceneMouseEvent* e) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* e) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;

        BlockPortView* portViewAtPos(QPointF pos) const;

        /**
         * Is schema valid?
         * @return
         */
        bool schemeValidity() const;

    private slots:
        /**
         * Evaluate concrete block.
         * @param blockId concrete block identifier
         */
        void evaluateBlock(Identifier blockId);

    public slots:
        void evaluate();
        void debug();
        void stopDebug();

        void setDisableDrop(bool v);

    signals:
        void error(const QString &msg);
};

#endif // BLOCKCANVAS_H

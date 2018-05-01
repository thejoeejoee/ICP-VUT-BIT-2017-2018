#ifndef BLOCKCANVAS_H
#define BLOCKCANVAS_H

#include "scrollarea.h"
#include <app/core/blockmanager.h>


class BlockCanvas : public ScrollArea
{
        Q_OBJECT
    private:
        bool m_dragOver = false;
        QPointF m_portStartPoint = QPointF(-1, -1);
        QPointF m_portOrigStartPoint;
        QPointF m_portEndPoint = QPointF();
        bool m_drawLine = false;
        BlockManager* m_blockManager;

    public:
        explicit BlockCanvas(QGraphicsWidget* parent = nullptr);
        ~BlockCanvas();

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    private:
        QList<Identifier> blockComputeOrder();

    protected:
        void dragEnterEvent(QGraphicsSceneDragDropEvent *e) override;
        void dragLeaveEvent(QGraphicsSceneDragDropEvent *e) override;
        void dropEvent(QGraphicsSceneDragDropEvent *e) override;

        void mousePressEvent(QGraphicsSceneMouseEvent* e) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* e) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;

        BlockPortView* portViewAtPos(QPointF pos) const;

    public slots:
        void evaluate();
};

#endif // BLOCKCANVAS_H

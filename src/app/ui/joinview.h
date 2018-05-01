#ifndef JOINVIEW_H
#define JOINVIEW_H

#include <app/core/identified.h>
#include <QGraphicsTextItem>
#include <QPen>
#include <QVariantAnimation>

class BlockManager;

class JoinView : public QObject, public QGraphicsLineItem
{
        Q_OBJECT

    private:
        QPen m_pen;
        Identifier m_dataId;
        BlockManager* m_blockManager = nullptr;
        bool m_hovered = false;
        QVariantAnimation* m_opacityAnimation;
        double m_currentOpacity = 0;

    public:
        JoinView(Identifier dataId, QGraphicsItem* parent = nullptr);

        void paint(
                QPainter * painter,
                const QStyleOptionGraphicsItem * option,
                QWidget * widget = nullptr) override;

    protected:
        void keyPressEvent(QKeyEvent* event) override;
        void mousePressEvent(QGraphicsSceneMouseEvent* e) override;
        void hoverMoveEvent(QGraphicsSceneHoverEvent * e) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* e) override;

        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
        QPainterPath nonStrokedShape() const;

    public:
        QPainterPath shape() const override;

        Identifier dataId() const;
        void setBlockManager(BlockManager* m);

    public slots:
        void adjustJoin();

    signals:
        void deleteRequest(Identifier joinId);
};

#endif // JOINVIEW_H

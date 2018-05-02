#ifndef JOINVIEW_H
#define JOINVIEW_H

#include <app/core/identified.h>
#include <QGraphicsTextItem>
#include <QPen>
#include <QVariantAnimation>

class BlockManager;


/**
 * @brief Class responsible for displaying join between output and input of two blocks.
 */
class JoinView : public QObject, public QGraphicsLineItem {
    Q_OBJECT

    private:
        QPen m_pen;
        Identifier m_dataId;
        BlockManager* m_blockManager = nullptr;
        bool m_hovered = false;
        QVariantAnimation* m_opacityAnimation;
        double m_currentOpacity = 0;

    public:
        /**
         * Creates Join based on unique identifier and optional parent.
         * @param dataId unique identifier
         * @param parent qt parent
         */
        explicit JoinView(Identifier dataId, QGraphicsItem* parent = nullptr);

        /**
         * Paints join via given painter.
         * @param painter painter to paint
         * @param option style of paint
         * @param widget optional widget
         */
        void paint(
                QPainter* painter,
                const QStyleOptionGraphicsItem* option,
                QWidget* widget
        ) override;

    protected:
        /**
         * Event receiver for key press on join.
         * @param event key press event
         */
        void keyPressEvent(QKeyEvent* event) override;
        /**
         * Event receiver for mouse click.
         * @param e mouse click event
         */
        void mousePressEvent(QGraphicsSceneMouseEvent* e) override;
        /**
         * Event receiver for hover move on item.
         * @param e mouse event
         */
        void hoverMoveEvent(QGraphicsSceneHoverEvent* e) override;
        /**
         * Event receiver for mouse leave.
         * @param e mouse leave event
         */
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* e) override;
        /**
         * Called when value is changed.
         * @param change item of change
         * @param value new value
         * @return changed value
         */
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
        /**
         * Getter for path of shape.
         * @return path
         */
        QPainterPath nonStrokedShape() const;

    public:
        /**
         * Getter for shape of join.
         * @return path
         */
        QPainterPath shape() const override;
        /**
         * Returns unique application identifier.
         * @return id
         */
        Identifier dataId() const;
        /**
         * Setter for block manager
         * @param m block manager
         */
        void setBlockManager(BlockManager* m);

    public slots:
        /**
         * Adjust position of displayed join after resize or scroll.
         */
        void adjustJoin();

    signals:
        /**
         * Request for join delete.
         * @param joinId id of deleted join
         */
        void deleteRequest(Identifier joinId);
};

#endif // JOINVIEW_H

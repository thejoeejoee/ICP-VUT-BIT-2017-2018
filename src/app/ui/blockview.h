#ifndef BLOCKVIEW_H
#define BLOCKVIEW_H

#include <app/core/identified.h>
#include <QGraphicsWidget>
#include <QSvgRenderer>

class Block;

/**
 * Class representing displayed block.
 */
class BlockView : public QGraphicsWidget {
    Q_OBJECT
    private:
        constexpr static int s_portsOffset = 15;
        constexpr static int s_portsMargin = 5;
        static const QSize s_blockSize;

        Block* m_data;
        QSvgRenderer m_imageRenderer;
        QColor m_backgroundColor;
        QColor m_backgroundSelectionColor;
        bool m_copyable = true;
        bool m_outputPortVisible = true;
        bool m_inputPortsVisible = true;

    public:
        /**
         * Construct view from block.
         * @param block core block
         * @param parent qt parent
         */
        explicit BlockView(Block* block, QGraphicsItem* parent = nullptr);

    protected:
        /**
         * Receiver for mouse move event.
         * @param event mouse event
         */
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
        /**
         * Receiver for mouse press event.
         * @param event mouse event
         */
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        /**
         * Receiver for mouse release event.
         * @param event mouse event
         */
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

        /**
         * Receiver for mouse click event.
         * @param event mouse event
         */
        void keyPressEvent(QKeyEvent* event) override;

        /**
         * Called on change of internal value.
         * @param change change of value
         * @param value new value
         * @return modified value
         */
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    public:
        /**
         * Paints block into canvas
         * @param painter painter to paint
         * @param option style
         * @param widget to render
         */
        void paint(
                QPainter* painter,
                const QStyleOptionGraphicsItem* option,
                QWidget* widget
        ) override;

        /**
         * Getter for ports offset.
         * @return port offset
         */
        static int portOffset();
        /**
         * Returns block data as block instance.
         * @return block
         */
        Block* blockData() const;
        /**
         * Returns graphic content of block.
         * @return pixel map
         */
        QPixmap pixmap();
        /**
         * Returns values of internal block.
         * @return mapping
         */
        QList<MappedDataValues> values() const;

    private slots:
        void repositionPorts();
        void resizeBoundingBox();

    public slots:
        /**
         * Setter for copyable flag
         * @param copyable is copyable?
         */
        void setCopyable(bool copyable);
        /**
         * Setter for output visibility.
         * @param visible state
         * @param animate has change animation
         */
        void setOutputVisible(bool visible, bool animate = true);
        /**
         * Setter for inputs visibility.
         * @param visible state
         * @param animate has change animation
         */
        void setInputsVisible(bool visible, bool animate = true);
        void setSingleInputVisible(int index, bool visible, bool animate = true);
        /**
         * Initialize all views for ports.
         */
        void initPortsViews();
        /**
         * Sets icon content.
         * @param image icon as string
         */
        void setSvgImage(const QString &image);
        /**
         * Sets background color for view.
         * @param color color
         */
        void setBackgroundColor(const QColor &color);
        /**
         * Sets background color for selected view.
         * @param color color
         */
        void setBackgroundSelectionColor(const QColor &color);

    signals:
        /**
         * Signal receiver for output ports visibility change.
         */
        void outputPortVisibleChanged();
        /**
         * Signal receiver for input ports visibility change.
         */
        void inputPortsVisibleChanged();
        /**
         * Receiver for delete request of block.
         * @param blockId unique identifier.
         */
        void deleteRequest(Identifier blockId);
};

#endif // BLOCKVIEW_H

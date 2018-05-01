#ifndef BLOCKVIEW_H
#define BLOCKVIEW_H

#include <app/core/identified.h>
#include <QGraphicsWidget>
#include <QSvgRenderer>

class Block;

class BlockView : public QGraphicsWidget
{
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
        explicit BlockView(Block* block, QGraphicsItem *parent = nullptr);

    protected:
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

        void keyPressEvent(QKeyEvent* event) override;

        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

    public:
        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget = nullptr) override;

        static int portOffset();
        Block* blockData() const;
        QPixmap pixmap();

    private slots:
        void repositionPorts();
        void resizeBoundingBox();

    public slots:
        void setCopyable(bool copyable);
        void setOutputVisible(bool visible, bool animate = true);
        void setInputsVisible(bool visible, bool animate = true);
        void setSingleInputVisible(int index, bool visible, bool animate = true);
        void initPortsViews();
        void setSvgImage(const QString& image);
        void setBackgroundColor(const QColor& color);
        void setBackgroundSelectionColor(const QColor& color);

    signals:
        void outputPortVisibleChanged();
        void inputPortsVisibleChanged();
        void deleteRequest(Identifier blockId);
};

#endif // BLOCKVIEW_H

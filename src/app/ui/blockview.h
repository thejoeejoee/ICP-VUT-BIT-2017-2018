#ifndef BLOCKVIEW_H
#define BLOCKVIEW_H

#include <QGraphicsWidget>
#include <QSvgRenderer>

class Block;

class BlockView : public QGraphicsWidget
{
        Q_OBJECT
    private:
        constexpr static int s_portsOffset = 15;
        constexpr static int s_portsMargin = 5;
        constexpr static int s_blockSize = 80;

        Block* m_data;
        QSvgRenderer m_imageRenderer;
        QColor m_backgroundColor;
        QColor m_backgroundSelectionColor;

    public:
        explicit BlockView(Block* block, QGraphicsItem *parent = nullptr);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent * e) override;

    public:
        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget = nullptr) override;

        Block* blockData() const;

    private slots:
        void repositionPorts();

    public slots:
        void initPortsViews();
        void setSvgImage(const QString& image);
        void setBackgroundColor(const QColor& color);
        void setBackgroundSelectionColor(const QColor& color);
};

#endif // BLOCKVIEW_H

#ifndef BLOCKVIEW_H
#define BLOCKVIEW_H

#include <QGraphicsWidget>

class Block;

class BlockView : public QGraphicsWidget
{
        Q_OBJECT
    private:
        Block* m_data;

    public:
        explicit BlockView(Block* block, QGraphicsItem *parent = nullptr);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

        Block* blockData() const;

    public slots:
//        void setSvgImage(const QString& image);
//        void setBackgroundColor(const QColor& color);
};

#endif // BLOCKVIEW_H

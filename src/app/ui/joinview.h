#ifndef JOINVIEW_H
#define JOINVIEW_H

#include <QGraphicsTextItem>
#include <QPen>


class JoinView : public QGraphicsLineItem
{
    private:
        QPen m_pen;

    public:
        JoinView(QGraphicsItem* parent = nullptr);

    protected:
        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
        void paint(
                QPainter * painter,
                const QStyleOptionGraphicsItem * option,
                QWidget * widget = nullptr) override;
};

#endif // JOINVIEW_H

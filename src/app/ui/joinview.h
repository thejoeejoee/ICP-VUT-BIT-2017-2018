#ifndef JOINVIEW_H
#define JOINVIEW_H

#include <app/core/identified.h>
#include <QGraphicsTextItem>
#include <QPen>


class JoinView : public QObject, public QGraphicsLineItem
{
        Q_OBJECT

    private:
        QPen m_pen;
        Identifier m_dataId;

    public:
        JoinView(Identifier dataId, QGraphicsItem* parent = nullptr);

    protected:
        QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
        void keyPressEvent(QKeyEvent* event) override;

        void paint(
                QPainter * painter,
                const QStyleOptionGraphicsItem * option,
                QWidget * widget = nullptr) override;
    public:
        Identifier dataId() const;

    signals:
        void deleteRequest(Identifier joinId);
};

#endif // JOINVIEW_H

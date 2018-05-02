#ifndef PLAINTEXT_H
#define PLAINTEXT_H

#include <QGraphicsTextItem>



class PlainText : public QGraphicsTextItem
{
        Q_OBJECT
    public:
        explicit PlainText(QGraphicsItem* parent = nullptr);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* e) override;

    signals:
        void clicked();
};

#endif // PLAINTEXT_H

#ifndef PLAINTEXT_H
#define PLAINTEXT_H

#include <QGraphicsTextItem>



class PlainText : public QGraphicsTextItem
{
        Q_OBJECT
    private:
        bool m_propagateMouse = false;

    public:
        explicit PlainText(QGraphicsItem* parent = nullptr);

        void setPropagateMouse(bool v);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* e) override;

    signals:
        void clicked();
};

#endif // PLAINTEXT_H

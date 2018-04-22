#ifndef BLOCKSSELECTION_H
#define BLOCKSSELECTION_H

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include "scrollarea.h"


class BlocksSelection: public ScrollArea
{
        Q_OBJECT
    private:
        QGraphicsLinearLayout* m_layout;

    public:
        explicit BlocksSelection(QGraphicsWidget* parent = nullptr);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    public slots:
        void addItem(QGraphicsWidget* item);
};

#endif // BLOCKSSELECTION_H

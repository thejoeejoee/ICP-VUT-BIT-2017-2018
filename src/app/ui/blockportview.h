#ifndef BLOCKPORTVIEW_H
#define BLOCKPORTVIEW_H

#include <app/core/base.h>
#include <QGraphicsWidget>


class BlockPortView: public QGraphicsWidget
{
        Q_OBJECT

    public:
        BlockPortView(QGraphicsItem* parent = nullptr);

        virtual ~BlockPortView() {}
        virtual MappedDataValues value() const = 0;
        virtual void setValue(MappedDataValues v) = 0;
};

#endif // BLOCKPORTVIEW_H

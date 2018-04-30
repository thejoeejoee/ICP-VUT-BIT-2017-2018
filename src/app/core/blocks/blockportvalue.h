#ifndef BLOCKPORTVALUE_H
#define BLOCKPORTVALUE_H

#include "blockport.h"
#include <QGraphicsWidget>


class BlockPortValue: public BlockPort
{
    public:
        BlockPortValue(bool editable = true, QGraphicsItem* parent = nullptr);

        QStringList labels() const override;
        void setValue(MappedDataValues v) override;
};

#endif // BLOCKPORTVALUE_H

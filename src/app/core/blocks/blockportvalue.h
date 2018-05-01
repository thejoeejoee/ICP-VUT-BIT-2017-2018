#ifndef BLOCKPORTVALUE_H
#define BLOCKPORTVALUE_H

#include "blockport.h"
#include <app/core/identified.h>
#include <QGraphicsWidget>


class BlockPortValue: public BlockPort
{
    public:
        BlockPortValue(Identifier blockId, Type::TypeE type, QGraphicsItem* parent = nullptr);

        QStringList labels() const override;
        void setValue(MappedDataValues v) override;
        void setIsOutput(bool v) override;
};

#endif // BLOCKPORTVALUE_H

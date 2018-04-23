#ifndef SINBLOCK_H
#define SINBLOCK_H

#include <app/core/block.h>
#include "blockportvalue.h"

class SinBlock : public Block
{
        FACTORIABLE_ID(Block, SinBlock, "sin_block")

    public:
        SinBlock(QGraphicsWidget* parent = nullptr);

        MappedDataValues evaluate(const QList<MappedDataValues>& inputData) override;
};

#endif // SINBLOCK_H

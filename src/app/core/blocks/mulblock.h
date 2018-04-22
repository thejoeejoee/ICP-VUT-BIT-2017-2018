#ifndef MULBLOCK_H
#define MULBLOCK_H

#include <app/core/block.h>
#include "blockportvalue.h"

class MulBlock : public Block
{
        FACTORIABLE_ID(Block, MulBlock, "mul_block")

    public:
        MulBlock(QGraphicsWidget* parent = nullptr);

        MappedDataValues evaluate(const QList<MappedDataValues>& inputData) override;
};

#endif // MULBLOCK_H

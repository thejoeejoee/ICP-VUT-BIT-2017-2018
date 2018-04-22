#ifndef COSBLOCK_H
#define COSBLOCK_H

#include <app/core/block.h>
#include "blockportvalue.h"

class CosBlock : public Block
{
        FACTORIABLE_ID(Block, CosBlock, "cos_block");

    public:
        CosBlock(QGraphicsWidget* parent = nullptr);

        MappedDataValues evaluate(const QList<MappedDataValues>& inputData) override;
};

#endif // COSBLOCK_H

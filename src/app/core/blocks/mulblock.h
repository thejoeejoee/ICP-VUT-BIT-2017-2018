#ifndef MULBLOCK_H
#define MULBLOCK_H

#include <app/core/block.h>
#include "blockportvalue.h"

/**
 * Block for multiplying operation.
 */
class MulBlock : public Block {
    FACTORIABLE_ID(Block, MulBlock, "mul_block")

    public:
        explicit MulBlock(QGraphicsWidget* parent = nullptr);

        /**
         * Evaluate input data into result.
         * @param inputData data to compute
         * @return result
         */
        MappedDataValues evaluate(const QList<MappedDataValues> &inputData) override;
};

#endif // MULBLOCK_H

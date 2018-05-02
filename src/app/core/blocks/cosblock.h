#ifndef COSBLOCK_H
#define COSBLOCK_H

#include <app/core/block.h>
#include "blockportvalue.h"

/**
 * Block for cosius operation.
 */
class CosBlock : public Block {
    FACTORIABLE_ID(Block, CosBlock, "cos_block")

    public:
        explicit CosBlock(QGraphicsWidget* parent = nullptr);

        /**
         * Evaluate cosinus operation.
         * @param inputData data to eval
         * @return new data
         */
        MappedDataValues evaluate(const QList<MappedDataValues> &inputData) override;
};

#endif // COSBLOCK_H

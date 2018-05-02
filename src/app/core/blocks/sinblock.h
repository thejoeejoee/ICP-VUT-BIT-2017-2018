#ifndef SINBLOCK_H
#define SINBLOCK_H

#include <app/core/block.h>
#include "blockportvalue.h"

/**
 * Block for sinus operation.
 */
class SinBlock : public Block {
    FACTORIABLE_ID(Block, SinBlock, "sin_block")

    public:
        explicit SinBlock(QGraphicsWidget* parent = nullptr);

        /**
         * Evaluate input data into result.
         * @param inputData data to compute
         * @return result
         */
        MappedDataValues evaluate(const QList<MappedDataValues> &inputData) override;
};

#endif // SINBLOCK_H

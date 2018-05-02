#ifndef SUBBLOCK_H
#define SUBBLOCK_H

#include <app/core/block.h>
#include "blockportvalue.h"

/**
 * Block for substracting operation.
 */
class SubBlock : public Block {
    FACTORIABLE_ID(Block, SubBlock, "sub_block")

    public:
        explicit SubBlock(QGraphicsWidget* parent = nullptr);

        /**
         * Creates result from input data.
         * @param inputData input data
         * @return new value
         */
        MappedDataValues evaluate(const QList<MappedDataValues> &inputData) override;
};

#endif // SUBBLOCK_H

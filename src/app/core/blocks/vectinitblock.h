#ifndef VECTINITBLOCK_H
#define VECTINITBLOCK_H

#include <app/core/block.h>
#include "blockportvalue.h"

/**
 * Block for constructing vector from scalar.
 */
class VectInitBlock : public Block {
    FACTORIABLE_ID(Block, VectInitBlock, "vect_init_block")

    public:
        explicit VectInitBlock(QGraphicsWidget* parent = nullptr);

        /**
         * Constructs new result from input data.
         * @param inputData data to process
         * @return new data
         */
        MappedDataValues evaluate(const QList<MappedDataValues> &inputData) override;
};

#endif // VECTINITBLOCK_H

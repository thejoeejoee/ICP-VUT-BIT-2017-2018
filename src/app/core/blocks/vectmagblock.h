#ifndef VECTMAGBLOCK_H
#define VECTMAGBLOCK_H

#include <app/core/block.h>
#include "blockportvalue.h"

/**
 * Block for computing vector magnitude.
 */
class VectMagBlock : public Block {
    FACTORIABLE_ID(Block, VectMagBlock, "vect_mag_block")

    public:
        explicit VectMagBlock(QGraphicsWidget* parent = nullptr);

        /**
         * Evaluates data into result.
         * @param inputData data to compute
         * @return result
         */
        MappedDataValues evaluate(const QList<MappedDataValues> &inputData) override;
};

#endif // VECTMAGBLOCK_H

/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

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

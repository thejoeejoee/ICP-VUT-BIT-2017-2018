/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

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

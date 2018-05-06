/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

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

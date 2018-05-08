/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

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

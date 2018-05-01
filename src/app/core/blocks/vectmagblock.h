#ifndef VECTMAGBLOCK_H
#define VECTMAGBLOCK_H

#include <app/core/block.h>
#include "blockportvalue.h"


class VectMagBlock: public Block
{
        FACTORIABLE_ID(Block, VectMagBlock, "vect_mag_block")

    public:
        VectMagBlock(QGraphicsWidget* parent = nullptr);

        MappedDataValues evaluate(const QList<MappedDataValues>& inputData) override;
};

#endif // VECTMAGBLOCK_H

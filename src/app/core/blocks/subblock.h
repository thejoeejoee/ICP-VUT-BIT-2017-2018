#ifndef SUBBLOCK_H
#define SUBBLOCK_H

#include <app/core/block.h>
#include "blockportvalue.h"

class SubBlock : public Block
{
        FACTORIABLE_ID(Block, SubBlock, "sub_block")

    public:
        SubBlock();
};

#endif // SUBBLOCK_H

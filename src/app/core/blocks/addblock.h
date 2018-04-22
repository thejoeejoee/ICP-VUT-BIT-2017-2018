#ifndef ADDBLOCK_H
#define ADDBLOCK_H

#include "../block.h"
#include "blockportvalue.h"

class AddBlock: public Block
{
        FACTORIABLE_ID(Block, AddBlock, "add_block")

    public:
        AddBlock(QGraphicsWidget* parent = nullptr);

        MappedDataValues evaluate(const QList<MappedDataValues>& inputData) override;
};

#endif // ADDBLOCK_H

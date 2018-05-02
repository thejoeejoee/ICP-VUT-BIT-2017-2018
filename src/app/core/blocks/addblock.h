#ifndef ADDBLOCK_H
#define ADDBLOCK_H

#include <app/core/block.h>
#include "blockportvalue.h"

/**
 * Block for adding operation.
 */
class AddBlock : public Block {
    FACTORIABLE_ID(Block, AddBlock, "add_block")

    public:
        /**
         * Create new block.
         * @param parent qt parent
         */
        explicit AddBlock(QGraphicsWidget* parent = nullptr);

        /**
         * Evaluate operation add on inputs data.
         * @param inputData input data
         * @return computed data
         */
        MappedDataValues evaluate(const QList<MappedDataValues> &inputData) override;
};

#endif // ADDBLOCK_H

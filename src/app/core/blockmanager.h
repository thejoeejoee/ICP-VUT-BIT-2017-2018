#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include <qmap.h>
#include "block.h"
#include "join.h"


class BlockManager {
        using Blocks = QMap<Identifier, Block *>;
        using Joins = QMap<Identifier, Join *>;

    protected:
        Blocks m_blocks;
        Joins m_joins;


    public:
        const Blocks &blocks() const;

        const Joins &joins() const;

        Block *block(Identifier id);

        Join *join(Identifier id);

        Block * addBlock(const TypeBlock &type);


};


#endif //Blockmanager_H

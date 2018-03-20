#include "blockmanager.h"


const BlockManager::Blocks &BlockManager::blocks() const {
    return m_blocks;
}

const BlockManager::Joins &BlockManager::joins() const {
    return m_joins;
}

Join *BlockManager::join(Identifier id) {
    return m_joins.value(id, nullptr);
}

Block *BlockManager::block(Identifier id) {
    return m_blocks.value(id, nullptr);
}

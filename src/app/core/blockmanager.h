#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include <QJsonObject>
#include <QMap>
#include "block.h"
#include "join.h"


class BlockManager {
    protected:
        QMap<Identifier, Block*> m_blocks;
        QMap<Identifier, Join*> m_joins;

    public:
        ~BlockManager();

        static QJsonObject blockToJson(Block* block);
        static Block* blockFromJson(const QJsonObject& json, QGraphicsWidget* parent = nullptr);
        static const char* blockMimeType();

        const QMap<Identifier, Block*>& blocks() const;
        const QMap<Identifier, Join*>& joins() const;

        void addBlock(Block* block);
        void addJoin(Join* join);

        Block* block(Identifier id) const;
        Join* join(Identifier id) const;

};


#endif //Blockmanager_H

#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include <QJsonObject>
#include <QMap>
#include "block.h"
#include "join.h"


class BlockManager: public QObject {
        Q_OBJECT

    protected:
        QMap<Identifier, Block*> m_blocks;
        QMap<Identifier, Join*> m_joins;
        bool m_disableDelete = false;

    public:
        BlockManager(): QObject{} {}
        ~BlockManager();

        static QJsonObject blockToJson(Block* block);
        static Block* blockFromJson(const QJsonObject& json, QGraphicsWidget* parent = nullptr);
        static const char* blockMimeType();

        const QMap<Identifier, Block*>& blocks() const;
        const QMap<Identifier, Join*>& joins() const;

        QSet<Identifier> blockBlocksInputs(Identifier blockId) const;
        QSet<Identifier> blockBlocksOutputs(Identifier blockId) const;
        QList<QPair<Identifier, Identifier> > blockInputs(Identifier blockId) const;
        QList<QPair<Identifier, Identifier> > blockOutputs(Identifier blockId) const;

        void addBlock(Block* block);
        void addJoin(Join* join);

        Block* block(Identifier id) const;
        Join* join(Identifier id) const;

    public slots:
        void setDisableDelete(bool v);
        void deleteBlock(Identifier id);
        void deleteJoin(Identifier id, Identifier excludeBlockId = -1);

    signals:
        // TODO doc
        void blockDeleted();
        void joinDeleted();
};


#endif //Blockmanager_H

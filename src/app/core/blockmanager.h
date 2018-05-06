/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include <QJsonObject>
#include <QMap>
#include "block.h"
#include "join.h"


/**
 * Manager for handling all blocks in schema.
 */
class BlockManager : public QObject {
    Q_OBJECT

    protected:
        /**
         * All blocks mapped to ids.
         */
        QMap<Identifier, Block*> m_blocks;
        /**
         * All joins mapped to ids.
         */
        QMap<Identifier, Join*> m_joins;
        /**
         * Is deleting disabled?
         */
        bool m_disableDelete = false;

    public:
        BlockManager() : QObject{} {}
        ~BlockManager() override;

        /**
         * Serialize block to json.
         * @param block block
         * @return serialized
         */
        static QJsonObject blockToJson(Block* block);
        /**
         * Load object from json.
         * @param json content
         * @param parent parent for block
         * @return created block
         */
        static Block* blockFromJson(const QJsonObject &json, QGraphicsWidget* parent = nullptr);
        /**
         * Returns block mime type for D&D.
         * @return mime type
         */
        static const char* blockMimeType();

        /**
         * All blocks getter.
         * @return blocks
         */
        const QMap<Identifier, Block*> &blocks() const;
        /**
         * All joins getter.
         * @return joins
         */
        const QMap<Identifier, Join*> &joins() const;

        /**
         * Returns all input ports for block defined by id.
         * @param blockId block id
         * @return all inputs
         */
        QSet<Identifier> blockBlocksInputs(Identifier blockId) const;
        /**
         * Returns output port block defined by id.
         * @param blockId block id
         * @return output
         */
        QSet<Identifier> blockBlocksOutputs(Identifier blockId) const;
        /**
         * Returns all input ports with source blocks for block defined by id.
         * @param blockId block id
         * @return all inputs mapped with blocks
         */
        QList<QPair<Identifier, Identifier> > blockInputs(Identifier blockId) const;
        /**
         * Returns output port mapped with target block block defined by id.
         * @param blockId block id
         * @return output port with block
         */
        QList<QPair<Identifier, Identifier> > blockOutputs(Identifier blockId) const;

        /**
         * Adds new block.
         * @param block new block
         */
        void addBlock(Block* block);
        /**
         * Adds new join.
         * @param join new join
         */
        void addJoin(Join* join);

        /**
         * Get block by id from schema.
         * @param id block identifer
         * @return found block
         */
        Block* block(Identifier id) const;

        /**
         * Get block by id from schema.
         * @param id
         * @return
         */
        Join* join(Identifier id) const;

    public slots:
        /**
         * Setter for delete disable flag.
         * @param v state
         */
        void setDisableDelete(bool v);
        /**
         * Slot to delete block.
         * @param id block identifier
         */
        void deleteBlock(Identifier id);
        /**
         * Slot to delete join.
         * @param id join identifier
         * @param excludeBlockId exlude block identifier
         */
        void deleteJoin(Identifier id, Identifier excludeBlockId = -1);

    signals:
        /**
         * On block deleted signal.
         */
        void blockDeleted();
        /**
         * On join deleted signal.
         */
        void joinDeleted();
};


#endif //Blockmanager_H

#include "schemeio.h"

#include <QJsonArray>

SchemeIO::SchemeIO(BlockManager* manager, QObject* parent): QObject (parent)
{
    m_manager = manager;
}

QJsonObject SchemeIO::exportToJson() const
{
    QJsonObject json;
    QJsonArray blocksJsonArr;
    QJsonArray joinsJsonArr;

    for(auto block: m_manager->blocks().values()) {
        QJsonObject blockJson = m_manager->blockToJson(block);
        // need deeper info
        blockJson["id"] = QJsonValue::fromVariant(block->id());
        blockJson["x"] = block->view()->pos().x();
        blockJson["y"] = block->view()->pos().y();

        blocksJsonArr.append(blockJson);
    }

    for(auto join: m_manager->joins().values()) {
        QJsonObject joinObject;
        joinObject["fromBlock"] = QJsonValue::fromVariant(join->fromBlock());
        joinObject["fromPort"] = QJsonValue::fromVariant(join->fromPort());
        joinObject["toBlock"] = QJsonValue::fromVariant(join->toBlock());
        joinObject["toPort"] = QJsonValue::fromVariant(join->toPort());

        joinsJsonArr.append(joinObject);
    }

    json["blocks"] = blocksJsonArr;
    json["joins"] = joinsJsonArr;

    return json;
}

void SchemeIO::loadFromJson(QJsonObject scheme, QGraphicsWidget* parent)
{
    // TODO check json
    QMap<Identifier, Identifier> mappedBlocksIds;

    for(auto blockJson: scheme["blocks"].toArray()) {
        const QJsonObject blockObject = blockJson.toObject();
        Block* block = m_manager->blockFromJson(blockObject, parent);
        m_manager->addBlock(block);

        mappedBlocksIds[blockObject["id"].toVariant().toUInt()] = block->id();

        block->view()->setCopyable(false);
        block->view()->setFlag(QGraphicsItem::ItemIsSelectable);
        block->view()->setFlag(QGraphicsItem::ItemIsMovable);
        block->view()->setX(blockObject["x"].toDouble());
        block->view()->setY(blockObject["y"].toDouble());
    }

    for(auto joinJson: scheme["joins"].toArray()) {
        const QJsonObject joinObject = joinJson.toObject();
        Identifier toBlock, toPort, fromBlock;
        toBlock = joinObject["toBlock"].toVariant().toUInt();
        toPort = joinObject["toPort"].toVariant().toUInt();
        fromBlock = joinObject["fromBlock"].toVariant().toUInt();

        auto join = new Join(mappedBlocksIds[fromBlock], 0,
                             mappedBlocksIds[toBlock], toPort, parent);
        join->setBlockManager(m_manager);
        m_manager->addJoin(join);
    }
}

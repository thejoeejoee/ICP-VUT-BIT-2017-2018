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

QString SchemeIO::jsonValid(const QJsonObject& scheme) const
{
    QMap<Identifier, QString> blocksTypes;
    if(scheme.keys().toSet() != QSet<QString>{"blocks", "joins"})
        return tr("Scheme structure is not valid.");

    const QMap<QString, QSet<QJsonValue::Type> > blockExpectedTypes{
        {"id", {QJsonValue::Double}},
        {"x", {QJsonValue::Double}},
        {"y", {QJsonValue::Double}},
        {"output_value", {QJsonValue::Double, QJsonValue::Null}},
        {"type", {QJsonValue::String}}
    };

    const QMap<QString, QJsonValue::Type> joinExpectedTypes{
        {"fromBlock", QJsonValue::Double},
        {"fromPort", QJsonValue::Double},
        {"toBlock", QJsonValue::Double},
        {"toPort", QJsonValue::Double}
    };

    // check blocks
    for(auto blockJson: scheme["blocks"].toArray()) {
        const QJsonObject blockObject = blockJson.toObject();
        if(blockObject.keys().toSet() !=
                (blockExpectedTypes.keys().toSet() | QSet<QString>{"input_values"})) {
            return tr("Block structure is not valid.");
        }

        for(auto key: blockExpectedTypes.keys()) {
            if(!blockExpectedTypes[key].contains(blockObject[key].type()))
                return tr("Types in block values do not match");
        }

        if(!Block::registeredItems().contains(blockObject["type"].toString()))
            return tr("Uknown block type.");

        const Identifier blockId = blockObject["id"].toVariant().toUInt();
        if(blocksTypes.keys().contains(blockId))
            return tr("Multiple blocks with same id.");

        blocksTypes.insert(blockId, blockObject["type"].toString());
    }

    for(auto joinJson: scheme["joins"].toArray()) {
        const QJsonObject joinObject = joinJson.toObject();

        for(auto key: joinExpectedTypes.keys()) {
            if(joinObject[key].type() != joinExpectedTypes[key])
                return tr("Types in join values do not match");
        }

        Identifier toBlock, toPort, fromBlock, fromPort;
        toBlock = joinObject["toBlock"].toVariant().toUInt();
        toPort = joinObject["toPort"].toVariant().toUInt();
        fromBlock = joinObject["fromBlock"].toVariant().toUInt();
        fromPort = joinObject["fromPort"].toVariant().toUInt();

        if(fromPort != 0)
            return tr("Output port id is too large.");
        if(!blocksTypes.keys().contains(toBlock) || !blocksTypes.keys().contains(fromBlock))
            return tr("Invalid blocks ids in join");
        if(Block::blockInputsCount(blocksTypes[toBlock]) <= static_cast<int>(toPort))
            return tr("Input port id is too large.");
    }

    return "";
}

void SchemeIO::loadFromJson(QJsonObject scheme, QGraphicsWidget* parent)
{
    const QString errorMsg = this->jsonValid(scheme);
    if(!errorMsg.isEmpty()) {
        emit this->error(errorMsg);
        return;
    }

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

#include "blockmanager.h"
#include <QJsonArray>

BlockManager::~BlockManager()
{
    for(auto join: m_joins.values())
        delete join;
}

QJsonObject BlockManager::blockToJson(Block* block)
{
    QJsonObject jsonObject;
    jsonObject["type"] = block->classId();
    jsonObject["output_value"] = block->outputPort()->value()["value"];

    QJsonArray input_values;
    for(auto port: block->inputPorts())
        input_values.append(port->value()["value"]);
    jsonObject["input_values"] = QJsonValue(input_values);

    return jsonObject;
}

Block* BlockManager::blockFromJson(const QJsonObject& json, QGraphicsWidget* parent)
{
    auto block = Block::createNew(json["type"].toString(), parent);
    for(int i = 0; i < block->inputPorts().length(); i++) {
        auto inputPort = block->inputPorts().at(i);
        QJsonArray values = json["input_values"].toArray();
        inputPort->setValue(MappedDataValues{{"value", values.at(i).toDouble()}, });
    }

    block->outputPort()->setValue(MappedDataValues{
                                      {"value", json["output_value"].toDouble()},
                                  });
    return block;
}

const char*BlockManager::blockMimeType()
{
    return "application/x-block-data";
}

const QMap<Identifier, Block*>& BlockManager::blocks() const
{
    return m_blocks;
}

const QMap<Identifier, Join*>& BlockManager::joins() const
{
    return m_joins;
}

void BlockManager::addBlock(Block* block)
{
    if(block == nullptr)
        return;
    m_blocks[block->id()] = block;
}

void BlockManager::addJoin(Join* join)
{
    if(join == nullptr)
        return;
    m_joins[join->id()] = join;
}

Join* BlockManager::join(Identifier id) const
{
    return m_joins.value(id, nullptr);
}

Block* BlockManager::block(Identifier id) const
{
    return m_blocks.value(id, nullptr);
}


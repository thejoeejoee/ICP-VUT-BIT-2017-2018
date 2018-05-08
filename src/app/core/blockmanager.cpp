/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "blockmanager.h"
#include <QJsonArray>

BlockManager::~BlockManager() {
    for (auto join: m_joins.values())
        delete join;
}

QJsonObject BlockManager::blockToJson(Block* block) {
    QJsonObject jsonObject;
    jsonObject["type"] = block->classId();
    jsonObject["output_value"] = QJsonValue::fromVariant(block->outputPort()->value()["value"]);

    QJsonArray input_values;
    for (auto port: block->inputPorts())
        input_values.append(QJsonValue::fromVariant(port->value()["value"]));
    jsonObject["input_values"] = QJsonValue(input_values);

    return jsonObject;
}

Block* BlockManager::blockFromJson(const QJsonObject &json, QGraphicsWidget* parent) {
    auto block = Block::createNew(json["type"].toString(), parent);
    for (int i = 0; i < block->inputPorts().length(); i++) {
        auto inputPort = block->inputPorts().at(i);
        QJsonArray values = json["input_values"].toArray();
        inputPort->setValue(MappedDataValues{{"value", values.at(i).toVariant()},});
    }

    block->outputPort()->setValue(MappedDataValues{
            {"value", json["output_value"].toVariant()},
    });
    return block;
}

const char* BlockManager::blockMimeType() {
    return "application/x-block-data";
}

const QMap<Identifier, Block*> &BlockManager::blocks() const {
    return m_blocks;
}

const QMap<Identifier, Join*> &BlockManager::joins() const {
    return m_joins;
}

QSet<Identifier> BlockManager::blockBlocksInputs(Identifier blockId) const {
    QSet<Identifier> result;
    for (auto join: m_joins.values()) {
        if (join->toBlock() == blockId)
            result.insert(join->fromBlock());
    }

    return result;
}

QSet<Identifier> BlockManager::blockBlocksOutputs(Identifier blockId) const {
    QSet<Identifier> result;
    for (auto join: m_joins.values()) {
        if (join->fromBlock() == blockId)
            result.insert(join->toBlock());
    }

    return result;
}


QList<QPair<Identifier, Identifier> > BlockManager::blockInputs(Identifier blockId) const {
    QList<QPair<Identifier, Identifier> > result;
    for (auto join: m_joins.values()) {
        if (join->toBlock() == blockId)
            result.append(qMakePair(join->fromBlock(), join->fromPort()));
    }

    return result;
}

QList<QPair<Identifier, Identifier> > BlockManager::blockOutputs(Identifier blockId) const {
    QList<QPair<Identifier, Identifier> > result;
    for (auto join: m_joins.values()) {
        if (join->fromBlock() == blockId)
            result.append(qMakePair(join->toBlock(), join->toPort()));
    }

    return result;
}

void BlockManager::addBlock(Block* block) {
    if (block == nullptr)
        return;
    m_blocks[block->id()] = block;
    connect(block, &Block::deleteRequest, this, &BlockManager::deleteBlock);
}

void BlockManager::addJoin(Join* join) {
    if (join == nullptr)
        return;
    m_joins[join->id()] = join;

    Block* fromBlock = m_blocks[join->fromBlock()];
    Block* toBlock = m_blocks[join->toBlock()];

    fromBlock->outputPort()->view()->animateHide();
    toBlock->inputPorts().at(join->toPort())->view()->animateHide();
    join->view()->adjustJoin();

    connect(join, &Join::deleteRequest, [this](Identifier id) { this->deleteJoin(id); });
    connect(fromBlock->view(), &BlockView::geometryChanged, join->view(), &JoinView::adjustJoin);
    connect(toBlock->view(), &BlockView::geometryChanged, join->view(), &JoinView::adjustJoin);
}

Join* BlockManager::join(Identifier id) const {
    return m_joins.value(id, nullptr);
}

void BlockManager::deleteBlock(Identifier id) {
    if (m_disableDelete)
        return;

    Block* b = m_blocks.value(id, nullptr);
    if (b == nullptr)
        return;

    QList<Identifier> joinIdsToDelete;

    for (auto join: m_joins.values()) {
        if (join->fromBlock() == b->id() || join->toBlock() == b->id())
            joinIdsToDelete.append(join->id());
    }

    for (int i = 0; i < joinIdsToDelete.length(); i++)
        this->deleteJoin(joinIdsToDelete.at(i), id);
    joinIdsToDelete.clear();

    m_blocks.remove(id);
    b->deleteLater();

    emit this->blockDeleted();
}

void BlockManager::deleteJoin(Identifier id, Identifier excludeBlockId) {
    if (m_disableDelete)
        return;

    Join* j = m_joins.value(id, nullptr);

    if (j == nullptr)
        return;

    if (j->fromBlock() != excludeBlockId)
        m_blocks[j->fromBlock()]->outputPort()->view()->animateShow();
    if (j->toBlock() != excludeBlockId)
        m_blocks[j->toBlock()]->inputPorts().at(j->toPort())->view()->animateShow();

    m_joins.remove(id);
    j->deleteLater();

    emit this->joinDeleted();
}

void BlockManager::setDisableDelete(bool v) {
    m_disableDelete = v;
}

Block* BlockManager::block(Identifier id) const {
    return m_blocks.value(id, nullptr);
}


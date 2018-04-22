#include "cosblock.h"

CosBlock::CosBlock(QGraphicsWidget* parent): Block(parent)
{
    m_ports = { new BlockPortValue };
}

MappedDataValues CosBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    return {{ "value", cos(inputData.at(0)["value"]) }};
}

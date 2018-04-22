#include "sinblock.h"

SinBlock::SinBlock(QGraphicsWidget* parent): Block(parent)
{
    m_ports = { new BlockPortValue };
}

MappedDataValues SinBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    return {{ "value", sin(inputData.at(0)["value"]) }};
}

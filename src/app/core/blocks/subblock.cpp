#include "subblock.h"

SubBlock::SubBlock(QGraphicsWidget* parent): Block(parent)
{
    m_ports = { new BlockPortValue, new BlockPortValue };
}

MappedDataValues SubBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    DataValue result = inputData.at(0)["value"];
    for(int i = 1; i < inputData.length(); i++)
        result -= inputData.at(0)["value"];
    return {{ "value", result }};
}

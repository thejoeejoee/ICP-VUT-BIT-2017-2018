#include "mulblock.h"

MulBlock::MulBlock(QGraphicsWidget* parent): Block(parent)
{
    m_ports = { new BlockPortValue, new BlockPortValue };
}

MappedDataValues MulBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    DataValue result = 1;
    for(const MappedDataValues& port: inputData)
        result *= port["value"];
    return {{"value", result}};
}

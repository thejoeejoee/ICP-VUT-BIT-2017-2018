#include "addblock.h"
#include <QString>

AddBlock::AddBlock(QGraphicsWidget* parent): Block(parent)
{
    m_ports = { new BlockPortValue, new BlockPortValue };
}

MappedDataValues AddBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    DataValue result = 0;
    for(const MappedDataValues& port: inputData)
        result += port["value"];
    return {{ "value", result }};
}


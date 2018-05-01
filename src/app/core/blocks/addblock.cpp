#include "addblock.h"
#include <QString>

AddBlock::AddBlock(QGraphicsWidget* parent): Block(parent)
{
    BlockView* blockView = this->view();
    blockView->setSvgImage(":/res/image/add_symbol.svg");
    this->setInputPorts({ new BlockPortValue(this->id(), Type::Scalar, blockView),
                          new BlockPortValue(this->id(), Type::Scalar, blockView) });
    this->setOutputPort(new BlockPortValue(this->id(), Type::Scalar, blockView));

    blockView->initPortsViews();
}

MappedDataValues AddBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    double result = 0;

    for(const MappedDataValues& port: inputData)
        result += port["value"].toDouble();
    return {{ "value", QVariant(result) }};
}


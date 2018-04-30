#include "mulblock.h"

MulBlock::MulBlock(QGraphicsWidget* parent): Block(parent)
{
    BlockView* blockView = this->view();
    blockView->setSvgImage(":/res/image/mul_symbol.svg");
    this->setInputPorts({ new BlockPortValue(this->id(), true, blockView),
                          new BlockPortValue(this->id(), true, blockView) });
    this->setOutputPort(new BlockPortValue(this->id(), false, blockView));

    blockView->initPortsViews();
}

MappedDataValues MulBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    DataValue result = 1;
    for(const MappedDataValues& port: inputData)
        result *= port["value"];
    return {{ "value", result }};
}

#include "subblock.h"

SubBlock::SubBlock(QGraphicsWidget* parent): Block(parent)
{
    BlockView* blockView = this->view();
    blockView->setSvgImage(":/res/image/sub_symbol.svg");
    this->setInputPorts({ new BlockPortValue(this->id(), true, blockView),
                          new BlockPortValue(this->id(), true, blockView) });
    this->setOutputPort(new BlockPortValue(this->id(), false, blockView));

    blockView->initPortsViews();
}

MappedDataValues SubBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    DataValue result = inputData.at(0)["value"];
    for(int i = 1; i < inputData.length(); i++)
        result -= inputData.at(0)["value"];
    return {{ "value", result }};
}

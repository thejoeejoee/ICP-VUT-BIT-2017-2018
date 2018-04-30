#include "cosblock.h"

CosBlock::CosBlock(QGraphicsWidget* parent): Block(parent)
{
    BlockView* blockView = this->view();
    blockView->setSvgImage(":/res/image/cos_symbol.svg");
    this->setInputPorts({ new BlockPortValue(true, blockView), });
    this->setOutputPort(new BlockPortValue(false, blockView));

    blockView->initPortsViews();
}

MappedDataValues CosBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    return {{ "value", cos(inputData.at(0)["value"]) }};
}

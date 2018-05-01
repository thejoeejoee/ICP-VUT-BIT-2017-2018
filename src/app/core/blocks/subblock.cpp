#include "subblock.h"

SubBlock::SubBlock(QGraphicsWidget* parent): Block(parent)
{
    BlockView* blockView = this->view();
    blockView->setSvgImage(":/res/image/sub_symbol.svg");
    this->setInputPorts({ new BlockPortValue(this->id(), Type::Scalar, blockView),
                          new BlockPortValue(this->id(), Type::Scalar, blockView) });
    this->setOutputPort(new BlockPortValue(this->id(), Type::Scalar, blockView));

    blockView->initPortsViews();
}

MappedDataValues SubBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    double result = inputData.at(0)["value"].toDouble();

    for(int i = 1; i < inputData.length(); i++)
        result -= inputData.at(i)["value"].toDouble();
    return {{ "value", QVariant(result) }};
}

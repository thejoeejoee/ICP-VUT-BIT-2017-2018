#include "mulblock.h"

MulBlock::MulBlock(QGraphicsWidget* parent): Block(parent)
{
    BlockView* blockView = this->view();
    blockView->setSvgImage(":/res/image/mul_symbol.svg");
    this->setInputPorts({ new BlockPortValue(this->id(), Type::Scalar, blockView),
                          new BlockPortValue(this->id(), Type::Scalar, blockView) });
    this->setOutputPort(new BlockPortValue(this->id(), Type::Scalar, blockView));

    blockView->initPortsViews();
}

MappedDataValues MulBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    double result = 1;
    for(const MappedDataValues& port: inputData)
        result *= port["value"].toDouble();
    return {{ "value", QVariant(result) }};
}

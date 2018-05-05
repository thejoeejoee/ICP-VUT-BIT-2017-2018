#include "sinblock.h"
#include <QtMath>

SinBlock::SinBlock(QGraphicsWidget* parent): Block(parent)
{
    BlockView* blockView = this->view();
    blockView->setSvgImage(":/res/image/sin_symbol.svg");
    this->setInputPorts({ new BlockPortValue(this->id(), Type::Angle, blockView), });
    this->setOutputPort(new BlockPortValue(this->id(), Type::Scalar, blockView));

    blockView->initPortsViews();
}

MappedDataValues SinBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    return {{ "value", QVariant(qSin(inputData.at(0)["value"].toDouble())) }};
}

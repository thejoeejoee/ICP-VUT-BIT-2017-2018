#include "vectmagblock.h"

VectMagBlock::VectMagBlock(QGraphicsWidget* parent): Block(parent)
{
    BlockView* blockView = this->view();
    blockView->setSvgImage(":/res/image/add_symbol.svg");
    this->setInputPorts({ new BlockPortValue(this->id(), Type::Vector, blockView)});
    this->setOutputPort(new BlockPortValue(this->id(), Type::Scalar, blockView));

    blockView->initPortsViews();
}

MappedDataValues VectMagBlock::evaluate(const QList<MappedDataValues>& inputData)
{
    Q_ASSERT(this->inputMatchesPorts(inputData));

    double result = 0;

    for(auto port: inputData) {
        QList<QVariant> inputVect = port["value"].toList();
        for(auto val: inputVect)
            result += pow(val.toDouble(), 2);
    }
    return {{ "value", QVariant(sqrt(result)) }};
}

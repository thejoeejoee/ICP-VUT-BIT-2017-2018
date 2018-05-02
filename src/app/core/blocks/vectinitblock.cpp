#include "vectinitblock.h"

VectInitBlock::VectInitBlock(QGraphicsWidget* parent) : Block(parent) {
    BlockView* blockView = this->view();
    // blockView->setSvgImage(":/res/image/add_symbol.svg"); // TODO
    this->setInputPorts({
                                new BlockPortValue(this->id(), Type::Scalar, blockView),
                                new BlockPortValue(this->id(), Type::Scalar, blockView),
                        });
    this->setOutputPort(new BlockPortValue(this->id(), Type::Vector, blockView));

    blockView->initPortsViews();
}

MappedDataValues VectInitBlock::evaluate(const QList<MappedDataValues> &inputData) {
    Q_ASSERT(this->inputMatchesPorts(inputData));

    QList<QVariant> result;

    for (auto port: inputData) {
        result.push_back(port["value"].toDouble());
    }
    return {{"value", QVariant(result)}};
}

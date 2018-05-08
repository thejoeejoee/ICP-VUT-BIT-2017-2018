/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "vectinitblock.h"

VectInitBlock::VectInitBlock(QGraphicsWidget* parent) : Block(parent) {
    BlockView* blockView = this->view();
    blockView->setSvgImage(":/res/image/vectoriaze_symbol.svg");
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

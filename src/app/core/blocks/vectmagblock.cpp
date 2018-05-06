/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "vectmagblock.h"
#include <QtMath>

VectMagBlock::VectMagBlock(QGraphicsWidget* parent) : Block(parent) {
    BlockView* blockView = this->view();
    blockView->setSvgImage(":/res/image/vect_mag_symbol.svg");
    this->setInputPorts({new BlockPortValue(this->id(), Type::Vector, blockView)});
    this->setOutputPort(new BlockPortValue(this->id(), Type::Scalar, blockView));

    blockView->initPortsViews();
}

MappedDataValues VectMagBlock::evaluate(const QList<MappedDataValues> &inputData) {
    Q_ASSERT(this->inputMatchesPorts(inputData));

    double result = 0;

    for (auto port: inputData) {
        QList<QVariant> inputVect = port["value"].toList();
        for (auto val: inputVect)
            result += qPow(val.toDouble(), 2);
    }
    return {{"value", QVariant(qSqrt(result))}};
}

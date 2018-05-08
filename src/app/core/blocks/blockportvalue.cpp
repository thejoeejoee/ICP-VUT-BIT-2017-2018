/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "blockportvalue.h"

#include <app/ui/blockportvalueview.h>

BlockPortValue::BlockPortValue(Identifier blockId, Type::TypeE type, QGraphicsItem* parent)
        : BlockPort(blockId, type) {
    BlockPortValueView* t = new BlockPortValueView(this, type, parent);
    this->setView(t);
}

QStringList BlockPortValue::labels() const {
    return {"value"};
}

void BlockPortValue::setValue(MappedDataValues v) {
    this->view()->setValue(v);
}

void BlockPortValue::setIsOutput(bool v) {
    BlockPort::setIsOutput(v);
    BlockPortValueView* view = qgraphicsitem_cast<BlockPortValueView*>(this->view());
    if (view != nullptr) {
        view->setEditable(!v);
        if (v)
            view->setValue(MappedDataValues{});
    }
}

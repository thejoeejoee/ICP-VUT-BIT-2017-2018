#include "blockportvalue.h"

#include <app/ui/blockportvalueview.h>

BlockPortValue::BlockPortValue(Identifier blockId, bool editable, QGraphicsItem* parent)
    : BlockPort(blockId)
{
    BlockPortValueView* t = new BlockPortValueView(this, editable, parent);
    this->setView(t);
}

QStringList BlockPortValue::labels() const
{
    return {"value"};
}

void BlockPortValue::setValue(MappedDataValues v)
{
    this->view()->setValue(v);
}

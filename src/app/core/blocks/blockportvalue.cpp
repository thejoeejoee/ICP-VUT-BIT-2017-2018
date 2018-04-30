#include "blockportvalue.h"

#include <app/ui/blockportvalueview.h>

BlockPortValue::BlockPortValue(bool editable, QGraphicsItem* parent): BlockPort()
{
    BlockPortValueView* t = new BlockPortValueView(editable, parent);
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

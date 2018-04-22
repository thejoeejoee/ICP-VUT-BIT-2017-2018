#include "blockportvalue.h"

BlockPortValue::BlockPortValue(): BlockPort() {}

QStringList BlockPortValue::labels() const
{
    return {"value"};
}

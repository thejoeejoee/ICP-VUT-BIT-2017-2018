#ifndef BLOCKPORTVALUE_H
#define BLOCKPORTVALUE_H

#include "blockport.h"

class BlockPortValue: public BlockPort
{
    public:
        BlockPortValue();

        QStringList labels() const override;
};

#endif // BLOCKPORTVALUE_H

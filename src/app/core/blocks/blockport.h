#ifndef BLOCKPORT_H
#define BLOCKPORT_H

#include <QStringList>

class BlockPort
{
    public:
        virtual QStringList labels() const = 0;
};

#endif // BLOCKPORT_H

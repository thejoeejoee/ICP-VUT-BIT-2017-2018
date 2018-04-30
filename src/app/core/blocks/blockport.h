#ifndef BLOCKPORT_H
#define BLOCKPORT_H

#include <QStringList>
#include <app/core/base.h>
#include <app/ui/blockportview.h>

class BlockPort
{
    private:
        BlockPortView* m_view;

    protected:
        void setView(BlockPortView* v);

    public:
        BlockPort();

        virtual ~BlockPort() {}
        virtual QStringList labels() const = 0;
        MappedDataValues value() const;
        virtual void setValue(MappedDataValues v) = 0;

        BlockPortView* view() const;
};

#endif // BLOCKPORT_H

#ifndef BLOCKPORT_H
#define BLOCKPORT_H

#include <QStringList>
#include <app/core/identified.h>
#include <app/core/base.h>
#include <app/ui/blockportview.h>

class BlockPort
{
    private:
        BlockPortView* m_view;
        Identifier m_blockId;
        bool m_isOutput = false;

    protected:
        void setView(BlockPortView* v);

    public:
        BlockPort(Identifier blockId);

        virtual ~BlockPort();
        virtual QStringList labels() const = 0;
        MappedDataValues value() const;
        virtual void setValue(MappedDataValues v) = 0;
        void setIsOutput(bool v);

        BlockPortView* view() const;
        Identifier blockId() const;
        bool isOutput() const;
};

#endif // BLOCKPORT_H

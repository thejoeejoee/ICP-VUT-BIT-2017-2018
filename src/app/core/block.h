#ifndef BLOCK_H
#define BLOCK_H


#include "base.h"
#include "identified.h"
#include "factoriable.h"
#include "factorybase.h"
#include "blocks/blockport.h"
#include "../ui/blockview.h"

class Block : public Identified, public Factoriable, public FactoryBase<Block> {
    private:
        QGraphicsWidget* m_parent;
        BlockView* m_view;

    protected:
        QList<BlockPort*> m_ports;

    public:
        Block(QGraphicsWidget* parent = nullptr);
        virtual ~Block();

        virtual MappedDataValues evaluate(const QList<MappedDataValues>& inputData) = 0;
        virtual QList<BlockPort*> ports() const;

        bool inputMatchesPorts(const QList<MappedDataValues>& inputData) const;
        QGraphicsWidget* parent() const;
        BlockView* view() const;
};


#endif //BLOCK_H

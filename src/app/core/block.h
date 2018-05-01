#ifndef BLOCK_H
#define BLOCK_H


#include "base.h"
#include "identified.h"
#include "factoriable.h"
#include "factorybase.h"
#include "blocks/blockport.h"
#include "../ui/blockview.h"

class Block : public QObject, public Identified, public Factoriable, public FactoryBase<Block> {
        Q_OBJECT

    private:
        QGraphicsWidget* m_parent;
        BlockView* m_view = nullptr;
        BlockPort* m_outputPort = nullptr;
        QList<BlockPort*> m_inputPorts;

    protected:
        void setOutputPort(BlockPort* p);
        void setInputPorts(const QList<BlockPort*>& inputPorts);

    public:
        Block(QGraphicsWidget* parent = nullptr);
        virtual ~Block();

        virtual MappedDataValues evaluate(const QList<MappedDataValues>& inputData) = 0;
        virtual QList<BlockPort*> inputPorts() const;
        BlockPort* outputPort() const;

        bool inputMatchesPorts(const QList<MappedDataValues>& inputData) const;
        QGraphicsWidget* parent() const;
        BlockView* view() const;

        bool validInputs() const;

    signals:
        void deleteRequest(Identifier blockId);
};


#endif //BLOCK_H

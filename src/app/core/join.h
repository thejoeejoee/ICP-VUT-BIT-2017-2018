#ifndef CONNECTION_H
#define CONNECTION_H


#include "identified.h"
#include <app/ui/joinview.h>

class BlockManager;

class Join : public QObject, public Identified {
        Q_OBJECT

    private:
        Identifier m_fromBlock;
        PortIdentifier m_fromPort;

        Identifier m_toBlock;
        PortIdentifier m_toPort;
        JoinView* m_view;

    public:
        Join(Identifier fromBlock,
             PortIdentifier fromPort,
             Identifier toBlock,
             PortIdentifier toPort, QGraphicsItem* parent = nullptr);
        ~Join();

        Identifier fromBlock() const;
        PortIdentifier fromPort() const;
        Identifier toBlock() const;
        PortIdentifier toPort() const;
        JoinView* view() const;

        void setBlockManager(BlockManager* m);

    signals:
        void deleteRequest(Identifier blockId);
};


#endif //CONNECTION_H

#ifndef CONNECTION_H
#define CONNECTION_H


#include "identified.h"
#include <app/ui/joinview.h>


class Join : public Identified {
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

        Identifier fromBlock() const;
        PortIdentifier fromPort() const;
        Identifier toBlock() const;
        PortIdentifier toPort() const;
        JoinView* view() const;
};


#endif //CONNECTION_H

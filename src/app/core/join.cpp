//
// Created by thejoeejoee on 20.3.18.
//

#include "join.h"

Join::Join(Identifier fromBlock, PortIdentifier fromPort, Identifier toBlock, PortIdentifier toPort, QGraphicsItem* parent):
    QObject{}, Identified{}, m_fromBlock{fromBlock}, m_fromPort{fromPort}, m_toBlock{toBlock}, m_toPort{toPort}
{
    m_view = new JoinView{this->id(), parent};

    connect(m_view, &JoinView::deleteRequest, this, &Join::deleteRequest);
}

Join::~Join()
{
    m_view->deleteLater();
}

Identifier Join::fromBlock() const
{
    return m_fromBlock;
}

PortIdentifier Join::fromPort() const
{
    return m_fromPort;
}

Identifier Join::toBlock() const
{
    return m_toBlock;
}

PortIdentifier Join::toPort() const
{
    return m_toPort;
}

JoinView* Join::view() const
{
    return m_view;
}

void Join::setBlockManager(BlockManager* m)
{
    m_view->setBlockManager(m);
}

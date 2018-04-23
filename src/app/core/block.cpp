#include "block.h"

Block::Block(QGraphicsWidget* parent): Identified(), Factoriable(), FactoryBase<Block>()
{
    m_parent = parent;
    m_view = new BlockView(this, parent);
}

Block::~Block()
{
    for(int i = 0; i < m_ports.length(); i++)
        delete m_ports[i];
}

QList<BlockPort*> Block::ports() const
{
    return m_ports;
}

bool Block::inputMatchesPorts(const QList<MappedDataValues>& inputData) const
{
    bool matches = true;
    matches = matches && inputData.length() == m_ports.length();
    for(int i = 0; i < m_ports.length(); i++)
        matches = matches && inputData.at(i).keys() == m_ports.at(i)->labels();
    return matches;
}

QGraphicsWidget* Block::parent() const
{
    return m_parent;
}

BlockView* Block::view() const
{
    return m_view;
}

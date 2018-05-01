#include "block.h"

void Block::setOutputPort(BlockPort* p)
{
    p->setIsOutput(true);
    m_outputPort = p;
}

void Block::setInputPorts(const QList<BlockPort*>& ports)
{
    for(auto p: ports)
        p->setIsOutput(false);
    m_ports = ports;
}

Block::Block(QGraphicsWidget* parent): QObject{}, Identified(), Factoriable(), FactoryBase<Block>()
{
    m_parent = parent;
    m_view = new BlockView(this, parent);
    m_outputPort = nullptr;

    m_view->setBackgroundColor(QColor("#4c4c4c"));
    m_view->setBackgroundSelectionColor(QColor("#0f81bc"));

    connect(m_view, &BlockView::deleteRequest, this, &Block::deleteRequest);
}

Block::~Block()
{
    m_view->deleteLater();
    delete m_outputPort;
    for(int i = 0; i < m_ports.length(); i++)
        delete m_ports[i];
}

QList<BlockPort*> Block::inputPorts() const
{
    return m_ports;
}

BlockPort* Block::outputPort() const
{
    return m_outputPort;
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


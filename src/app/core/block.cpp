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
    m_inputPorts = ports;
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
    for(int i = 0; i < m_inputPorts.length(); i++)
        delete m_inputPorts[i];
}

QList<BlockPort*> Block::inputPorts() const
{
    return m_inputPorts;
}

BlockPort* Block::outputPort() const
{
    return m_outputPort;
}

bool Block::inputMatchesPorts(const QList<MappedDataValues>& inputData) const
{
    bool matches = true;
    matches = matches && inputData.length() == m_inputPorts.length();
    for(int i = 0; i < m_inputPorts.length(); i++)
        matches = matches && inputData.at(i).keys() == m_inputPorts.at(i)->labels();
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

bool Block::validInputs() const
{
    bool valid = true;
    for(auto port: m_inputPorts) {
        if(port->isConnected())
            continue;
        valid = valid && port->valid();
    }

    return valid;
}


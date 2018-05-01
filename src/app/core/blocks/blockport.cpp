#include "blockport.h"

void BlockPort::setView(BlockPortView* v)
{
    m_view = v;
}

BlockPort::BlockPort(Identifier blockId)
{
    m_view = nullptr;
    m_blockId = blockId;
}

BlockPort::~BlockPort() {
    m_view->deleteLater();
}

MappedDataValues BlockPort::value() const
{
    return m_view->value();
}

void BlockPort::setIsOutput(bool v)
{
    m_isOutput = v;
}

BlockPortView* BlockPort::view() const
{
    return m_view;
}

Identifier BlockPort::blockId() const
{
    return m_blockId;
}

bool BlockPort::isOutput() const
{
    return m_isOutput;
}

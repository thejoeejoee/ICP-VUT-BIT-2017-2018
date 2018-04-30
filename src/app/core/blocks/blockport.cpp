#include "blockport.h"

void BlockPort::setView(BlockPortView* v)
{
    m_view = v;
}

BlockPort::BlockPort()
{
    m_view = nullptr;
}

MappedDataValues BlockPort::value() const
{
    return m_view->value();
}

BlockPortView* BlockPort::view() const
{
    return m_view;
}

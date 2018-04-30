#include "portregister.h"

PortRegister::PortRegister(QObject *parent) : QObject(parent)
{

}

BlockPortView* PortRegister::attachedPort(QPoint pos) const
{
    for(BlockPortView* port: m_ports) {
        if(port == nullptr)
            continue;
        if(port->geometry().contains(pos))
            return port;
    }

    return nullptr;
}

void PortRegister::registerPort(BlockPortView* port)
{
    m_ports.append(port);
}

void PortRegister::unregisterPort(BlockPortView* port)
{
    m_ports.removeAll(port);
}

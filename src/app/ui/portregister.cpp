#include "portregister.h"

PortRegister::PortRegister(QObject *parent) : QObject(parent)
{

}

PortView* PortRegister::attachedPort(QPoint pos) const
{
    for(PortView* port: m_ports) {
        if(port == nullptr)
            continue;
        if(port->geometry().contains(pos))
            return port;
    }

    return nullptr;
}

void PortRegister::registerPort(PortView* port)
{
    m_ports.append(port);
}

void PortRegister::unregisterPort(PortView* port)
{
    m_ports.removeAll(port);
}

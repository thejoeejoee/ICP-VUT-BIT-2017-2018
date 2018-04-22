#ifndef PORTREGISTER_H
#define PORTREGISTER_H

#include <QObject>
#include <QVector>
#include "portview.h"

class PortRegister : public QObject
{
        Q_OBJECT
    private:
        QVector<PortView*> m_ports;

    public:
        explicit PortRegister(QObject *parent = nullptr);

        PortView* attachedPort(QPoint pos) const;

    public slots:
        void registerPort(PortView* port);
        void unregisterPort(PortView* port);
};

#endif // PORTREGISTER_H

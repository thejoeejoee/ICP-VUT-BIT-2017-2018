#ifndef PORTREGISTER_H
#define PORTREGISTER_H

#include <QObject>
#include <QVector>
#include "blockportview.h"

class PortRegister : public QObject
{
        Q_OBJECT
    private:
        QVector<BlockPortView*> m_ports;

    public:
        explicit PortRegister(QObject *parent = nullptr);

        BlockPortView* attachedPort(QPoint pos) const;

    public slots:
        void registerPort(BlockPortView* port);
        void unregisterPort(BlockPortView* port);
};

#endif // PORTREGISTER_H

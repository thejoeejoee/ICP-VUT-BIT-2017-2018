#ifndef CONNECTION_H
#define CONNECTION_H


#include "identified.h"

class Join : public Identified {
    protected:
        Identifier m_from_block;
        PortIdentifier m_from_port;

        Identifier m_to_block;
        PortIdentifier m_to_port;
};


#endif //CONNECTION_H

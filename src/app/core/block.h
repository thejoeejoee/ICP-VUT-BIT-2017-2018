#ifndef BLOCK_H
#define BLOCK_H


#include "base.h"
#include "identified.h"
#include "typeblock.h"

class Block : public Identified {
    protected:
        TypeBlock *m_type{};

    public:
        explicit Block(TypeBlock * type, ...) {
            m_type = type;
        }

};


#endif //BLOCK_H

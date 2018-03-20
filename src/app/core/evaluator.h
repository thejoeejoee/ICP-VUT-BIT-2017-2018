#ifndef EVALUATOR_H
#define EVALUATOR_H


#include "blockmanager.h"

class Evaluator {
    protected:
        const BlockManager * m_manager;
    public:
        explicit Evaluator(const BlockManager * manager);;
};


#endif //EVALUATOR_H

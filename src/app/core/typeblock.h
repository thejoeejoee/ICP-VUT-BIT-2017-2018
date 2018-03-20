#ifndef TYPEBLOCK_H
#define TYPEBLOCK_H

#include <QList>
#include "typedata.h"
#include "base.h"
#include "identified.h"
#include "data.h"

using EvaluationCallback = Data (*)(QList<Data>);

class TypeBlock : public Identified {
    public:
        TypeData output_port() const;

        QList<TypeData *> input_ports() const;

        Data evaluate(QList<Data> &) const;

        TypeBlock(TypeData output, QList<TypeData *> inputs, EvaluationCallback evaluator);

    protected:
        QList<TypeData *> m_input_ports;
        TypeData m_output_port;
        EvaluationCallback m_evaluator;

};


#endif //TYPEBLOCK_H

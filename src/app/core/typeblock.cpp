#include "typeblock.h"

TypeData TypeBlock::output_port() const {
    return m_output_port;
}

QList<TypeData *> TypeBlock::input_ports() const {
    return m_input_ports;
}

TypeBlock::TypeBlock(TypeData output, QList<TypeData *> inputs, EvaluationCallback evaluator) {
    m_output_port = output;
    m_input_ports = inputs;
    m_evaluator = evaluator;
}

Data TypeBlock::evaluate(QList<Data> &inputs) const {
    return m_evaluator(inputs);
}

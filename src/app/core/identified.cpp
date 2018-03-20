#include "identified.h"

Identifier Identified::m_counter = 0;

Identifier Identified::id() const {
    return m_id;
}

Identified::Identified() {
    m_id = ++m_counter;
}

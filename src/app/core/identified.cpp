/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#include "identified.h"

Identifier Identified::m_counter = 0;

Identifier Identified::id() const {
    return m_id;
}

Identified::Identified() {
    m_id = ++m_counter;
}

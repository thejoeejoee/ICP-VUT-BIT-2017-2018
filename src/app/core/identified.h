/**
 * Part of block editor project for ICP at FIT BUT 2017-2018.
 *
 * @package ICP-2017-2018
 * @authors Son Hai Nguyen xnguye16@stud.fit.vutbr.cz, Josef Kolář xkolar71@stud.fit.vutbr.cz
 * @date 06-05-2018
 * @version 1.0
 */

#ifndef IDENTIFIED_H
#define IDENTIFIED_H


#include "base.h"

/**
 * Base class for identifiable entity.
 */
class Identified {
    private:
        static Identifier m_counter;
        Identifier m_id{};

    protected:
        Identified();

        Identified(const Identified &) = default;

        /**
         * Comparsion of two entities.
         * @return is equal
         */
        Identified &operator=(const Identified &) = default;

    public:
        /**
         * Returns unique identifier.
         * @return
         */
        Identifier id() const;
};


#endif //Identified_H

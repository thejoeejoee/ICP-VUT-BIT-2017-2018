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

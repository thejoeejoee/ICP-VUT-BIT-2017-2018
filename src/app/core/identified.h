#ifndef IDENTIFIED_H
#define IDENTIFIED_H


#include "base.h"

class Identified {
    private:
        static Identifier m_counter;
        Identifier m_id{};

    protected:
        Identified();

        Identified(const Identified &) = default;

        Identified &operator=(const Identified &) = default;

    public:
        Identifier id() const;
};


#endif //Identified_H

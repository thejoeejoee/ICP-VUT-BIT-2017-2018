#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>


class InvalidInputError: std::runtime_error {
    public:
        InvalidInputError(const char* msg): std::runtime_error(msg) {}

        // exception interface
    public:
        const char* what() const noexcept override;
};

#endif // EXCEPTIONS_H

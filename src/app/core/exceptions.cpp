#include "exceptions.h"

const char* InvalidInputError::what() const noexcept
{
    return std::runtime_error::what();
}

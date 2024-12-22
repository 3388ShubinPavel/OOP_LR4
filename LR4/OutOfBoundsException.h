#pragma once
#include <stdexcept>

class OutOfBoundsException : public std::out_of_range {
public:
    OutOfBoundsException() 
        : std::out_of_range("Attack coordinates are out of bounds.") {}
};
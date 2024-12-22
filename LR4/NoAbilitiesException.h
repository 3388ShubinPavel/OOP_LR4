#pragma once
#include <stdexcept>

class NoAbilitiesException : public std::runtime_error {
public:
    NoAbilitiesException() 
        : std::runtime_error("No abilities available to apply.") {}
};
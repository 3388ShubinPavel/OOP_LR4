#pragma once
#include <stdexcept>

class InvalidShipPlacementException : public std::runtime_error {
public:
    InvalidShipPlacementException() 
        : std::runtime_error("Invalid ship placement: Ship overlaps or is too close to another ship.") {}
};
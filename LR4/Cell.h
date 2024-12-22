#pragma once

#include <iostream>
#include "Ship.h"

enum class CellStatus {
    Unknown,
    Empty,
    Ship,
    Damaged,
    Destroyed
};

class Cell {
private:
    CellStatus status;
    Ship* ship;
    int segmentIndex;
public:
    Cell();
    CellStatus getStatus() const;
    Ship* getShip() const;
    void setShip(Ship* s, int index);
    bool isEmpty() const;
    void attack(bool doubleDamage);
    void setEmpty();
    void setStatus(CellStatus status); 
};

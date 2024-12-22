#include "Cell.h"

Cell::Cell() : status(CellStatus::Unknown), ship(nullptr), segmentIndex(-1) {}

CellStatus Cell::getStatus() const {
    return status;
}

void Cell::setShip(Ship* s, int index) {
    ship = s;
    segmentIndex = index;
    status = CellStatus::Ship;
}

bool Cell::isEmpty() const {
    return status == CellStatus::Empty || status == CellStatus::Unknown;
}

void Cell::attack(bool doubleDamage) {
    if (status == CellStatus::Unknown) {
        status = CellStatus::Empty; 
    } else if (status == CellStatus::Ship && ship != nullptr) {
        if (doubleDamage) {
            ship->forceDestroySegment(segmentIndex);
            status = CellStatus::Destroyed;  
        } else {
            ship->takeDamage(segmentIndex);
            if (ship->getSegment(segmentIndex).getStatus() == SegmentStatus::Damaged) {
                status = CellStatus::Damaged;  
            }
        }
    } else if (status == CellStatus::Damaged) {
        if (doubleDamage) {
            ship->forceDestroySegment(segmentIndex);
            status = CellStatus::Destroyed;
        } else {
            ship->takeDamage(segmentIndex);
            if (ship->getSegment(segmentIndex).getStatus() == SegmentStatus::Destroyed) {
                status = CellStatus::Destroyed;
            }
        }
    }
}

Ship* Cell::getShip() const {
    return ship;
}

void Cell::setEmpty() {
    status = CellStatus::Empty;
    ship = nullptr;
}

void Cell::setStatus(CellStatus newStatus) {
    status = newStatus; 
}

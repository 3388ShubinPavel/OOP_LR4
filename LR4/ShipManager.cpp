#include "ShipManager.h"

ShipManager::ShipManager(int numShips, const std::vector<int>& sizes) {
    for (int size : sizes) {
        ships.push_back(new Ship(size, false)); 
    }
}

Ship& ShipManager::getShip(int index) {
    return *ships.at(index);
}

const Ship& ShipManager::getShip(int index) const {
    return *ships.at(index);
}

std::vector<Ship*>& ShipManager::getAllShips() {
    return ships;
}

ShipManager::~ShipManager() {
    for (Ship* ship : ships) {
        delete ship;  
    }
}
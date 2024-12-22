#include "Bombardment.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void BombardmentAbility::apply(InfoHolder& infoHolder) {
    std::vector<Ship*>& ships = infoHolder.shipManager.getAllShips();  
    if (ships.empty()) {
        std::cout << "No ships available for bombardment!" << std::endl;
        return;
    }

    int randomShipIndex = std::rand() % ships.size();
    Ship& selectedShip = infoHolder.shipManager.getShip(randomShipIndex);  

    int segmentCount = selectedShip.getSegmentCount();

    if (segmentCount == 0) {
        std::cout << "Selected ship has no segments!" << std::endl;
        return;
    }

    int randomSegmentIndex = std::rand() % segmentCount;
    selectedShip.takeDamage(randomSegmentIndex);


    std::cout << "Bombardment applied: 1 damage to random segment of ship at index "
              << randomShipIndex << ", segment " << randomSegmentIndex << "." << std::endl;
}


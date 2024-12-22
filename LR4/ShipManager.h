#pragma once

#include <vector>
#include "Ship.h"

class ShipManager {
private:
    std::vector<Ship*> ships;
public:
    ShipManager(int numShips, const std::vector<int>& sizes);
    
    Ship& getShip(int index);
    const Ship& getShip(int index) const;

    std::vector<Ship*>& getAllShips();

    ~ShipManager();

    ShipManager(const ShipManager& other) = default;
    ShipManager(ShipManager&& other) noexcept = default;
    ShipManager& operator=(const ShipManager& other) = default;
    ShipManager& operator=(ShipManager&& other) noexcept = default;
};

#pragma once

#include <vector>
#include <fstream>
#include "Cell.h"
#include "AbilityManager.h"
#include "ShipManager.h"
#include "OutOfBoundsException.h"
#include "InvalidShipPlacementException.h"

class AbilityManager;

class GameField {
private:
    int width, height;
    std::vector<std::vector<Cell>> grid;
    ShipManager* shipManager;
    AbilityManager* abilityManager; 
    bool isValidPlacement(const Ship& ship, int x, int y) const;

public:
    GameField(int w, int h, ShipManager& manager);

    GameField(const GameField& other);
    GameField(GameField&& other) noexcept;

    GameField& operator=(const GameField& other);
    GameField& operator=(GameField&& other) noexcept;

    bool placeShip(int shipIndex, int x, int y, bool vertical);
    void attackCell(int x, int y, bool doubleDamage);
    Cell& getCell(int x, int y);
    const Cell& getCell(int x, int y) const;
    int getWidth() const;
    int getHeight() const;
    void display(bool hideShips) const;
    bool allShipsDestroyed() const;
    void saveToFile(std::ofstream& outFile) const;
    void loadFromFile(std::ifstream& inFile);
    void loadFromStream(std::istream& inStream);
};

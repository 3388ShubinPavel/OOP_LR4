#include "GameField.h"
#include <iostream>
#include <stdexcept>

GameField::GameField(int w, int h, ShipManager& manager) 
    : width(w), height(h), grid(h, std::vector<Cell>(w)), shipManager(&manager) {}

GameField::GameField(const GameField& other) 
    : width(other.width), height(other.height), grid(other.grid), shipManager(other.shipManager) {}

GameField::GameField(GameField&& other) noexcept 
    : width(other.width), height(other.height), grid(std::move(other.grid)), shipManager(other.shipManager) {
    other.shipManager = nullptr; 
    other.abilityManager = nullptr;
}

int GameField::getWidth() const { 
    return width;
}

int GameField::getHeight() const {
    return height;
}

GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        grid = other.grid;
        shipManager = other.shipManager;
    }
    return *this;
}

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        width = other.width;
        height = other.height;
        grid = std::move(other.grid);
        shipManager = other.shipManager;
        other.shipManager = nullptr;
    }
    return *this;
}

bool GameField::isValidPlacement(const Ship& ship, int x, int y) const {
    int length = ship.getLength();
    if (ship.isVerticalOrientation()) {
        if (y + length > height) return false;
        for (int i = 0; i < length; ++i) {
            if (!grid[y + i][x].isEmpty()) return false;
        }
    } else {
        if (x + length > width) return false;
        for (int i = 0; i < length; ++i) {
            if (!grid[y][x + i].isEmpty()) return false;
        }
    }
    return true;
}

bool GameField::placeShip(int shipIndex, int x, int y, bool vertical) {
    Ship& ship = shipManager->getShip(shipIndex);
    ship.setOrientation(vertical);

    if (!isValidPlacement(ship, x, y)){
        throw InvalidShipPlacementException();
    }

    if (vertical) {
        for (int i = 0; i < ship.getLength(); ++i) {
            grid[y + i][x].setShip(&ship, i);
        }
    } else {
        for (int i = 0; i < ship.getLength(); ++i) {
            grid[y][x + i].setShip(&ship, i);
        }
    }
    return true;
}

void GameField::attackCell(int x, int y, bool doubleDamage) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw OutOfBoundsException();
    }

    Cell& cell = grid[y][x];
    cell.attack(doubleDamage);

    if (cell.getStatus() == CellStatus::Destroyed && cell.getShip() != nullptr) { //вынести в класс гейм
        Ship* ship = cell.getShip();
        
        if (ship->isDestroyed()) {
            std::cout << "Enemy ship destroyed!" << std::endl;
            
            abilityManager->grantRandomAbility(); 
        }
    }
}


void GameField::display(bool hideShips) const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            const Cell& cell = getCell(i, j);
            char cellChar = '.';

            if (hideShips && cell.getStatus() == CellStatus::Ship) {
                cellChar = '.';  
            } else {
                switch (cell.getStatus()) {
                    case CellStatus::Damaged:
                        cellChar = 'X'; 
                        break;
                    case CellStatus::Destroyed:
                        cellChar = 'D';  
                        break;
                    case CellStatus::Empty:
                        cellChar = 'O';  
                        break;
                    case CellStatus::Ship:
                        cellChar = 'S';  
                        break;
                    default:
                        break;
                }
            }

            std::cout << cellChar << " ";  
        }
        std::cout << std::endl;
    }
}





const Cell& GameField::getCell(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Coords is out of range");
    }
    return grid[y][x]; 
}

Cell& GameField::getCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Coords is out of range");
    }
    return grid[y][x]; 
}


bool GameField::allShipsDestroyed() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const Cell& cell = grid[y][x];
            if (cell.getStatus() == CellStatus::Ship) {  
                Ship* ship = cell.getShip();
                if (ship != nullptr && !ship->isDestroyed()) {  
                    return false;  
                }
            }
        }
    }
    return true; 
}

void GameField::saveToFile(std::ofstream& outFile) const {
    int width = getWidth();
    int height = getHeight();
    outFile.write(reinterpret_cast<const char*>(&width), sizeof(width));
    outFile.write(reinterpret_cast<const char*>(&height), sizeof(height));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const Cell& cell = getCell(x, y);  

            CellStatus status = cell.getStatus();
            outFile.write(reinterpret_cast<const char*>(&status), sizeof(status));

            if (cell.getShip() != nullptr) {
                Ship* ship = cell.getShip();
                int length = ship->getLength();
                bool isVertical = ship->isVerticalOrientation();

                outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
                outFile.write(reinterpret_cast<const char*>(&isVertical), sizeof(isVertical));

                for (int i = 0; i < length; ++i) {
                    SegmentStatus segmentStatus = ship->getSegment(i).getStatus();
                    outFile.write(reinterpret_cast<const char*>(&segmentStatus), sizeof(segmentStatus));
                }
            } else {
                int emptyFlag = -1;
                outFile.write(reinterpret_cast<const char*>(&emptyFlag), sizeof(emptyFlag));
            }
        }
    }
}

void GameField::loadFromFile(std::ifstream& inFile) {
    int width, height;
    inFile.read(reinterpret_cast<char*>(&width), sizeof(width));
    inFile.read(reinterpret_cast<char*>(&height), sizeof(height));

    grid = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
    this->width = width;
    this->height = height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Cell& cell = getCell(x, y);  

            CellStatus status;
            inFile.read(reinterpret_cast<char*>(&status), sizeof(status));
            cell.setStatus(status);


            int length;
            inFile.read(reinterpret_cast<char*>(&length), sizeof(length));

            if (length == -1) {
                continue;
            }

            bool isVertical;
            inFile.read(reinterpret_cast<char*>(&isVertical), sizeof(isVertical));

            Ship* ship = new Ship(length, isVertical); 

            for (int i = 0; i < length; ++i) {
                SegmentStatus segmentStatus;
                inFile.read(reinterpret_cast<char*>(&segmentStatus), sizeof(segmentStatus));
                ship->getSegment(i).setStatus(segmentStatus);  
            }

            shipManager->getAllShips().push_back(ship);

            bool placed = false;
            for (int i = 0; i < height && !placed; ++i) {
                for (int j = 0; j < width && !placed; ++j) {
                    if (isValidPlacement(*ship, j, i)) {
                        int shipIndex = shipManager->getAllShips().size() - 1;  
                        placeShip(shipIndex, j, i, isVertical);  
                        placed = true;
                    }
                }
            }

            if (!placed) {
                throw std::runtime_error("Failed to place ship during loading.");
            }
        }
    }
}

void GameField::loadFromStream(std::istream& inStream) {
    int width, height;
    inStream.read(reinterpret_cast<char*>(&width), sizeof(width));
    inStream.read(reinterpret_cast<char*>(&height), sizeof(height));

    grid = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
    this->width = width;
    this->height = height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Cell& cell = getCell(x, y);  

            CellStatus status;
            inStream.read(reinterpret_cast<char*>(&status), sizeof(status));
            cell.setStatus(status);

            int length;
            inStream.read(reinterpret_cast<char*>(&length), sizeof(length));

            if (length == -1) {
                continue;
            }

            bool isVertical;
            inStream.read(reinterpret_cast<char*>(&isVertical), sizeof(isVertical));

            Ship* ship = new Ship(length, isVertical); 

            for (int i = 0; i < length; ++i) {
                SegmentStatus segmentStatus;
                inStream.read(reinterpret_cast<char*>(&segmentStatus), sizeof(segmentStatus));
                ship->getSegment(i).setStatus(segmentStatus); 
            }

            shipManager->getAllShips().push_back(ship);

            bool placed = false;
            for (int i = 0; i < height && !placed; ++i) {
                for (int j = 0; j < width && !placed; ++j) {
                    if (isValidPlacement(*ship, j, i)) {
                        int shipIndex = shipManager->getAllShips().size() - 1; 
                        placeShip(shipIndex, j, i, isVertical);  
                        placed = true;
                    }
                }
            }

            if (!placed) {
                throw std::runtime_error("Failed to place ship during loading.");
            }
        }
    }
}







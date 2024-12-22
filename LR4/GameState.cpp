#include "GameState.h"
#include <stdexcept>

GameState::GameState(int fieldWidth, int fieldHeight, ShipManager& userManager, ShipManager& enemyManager)
    : userField(fieldWidth, fieldHeight, userManager), 
      enemyField(fieldWidth, fieldHeight, enemyManager),
      userManager(userManager),  
      enemyManager(enemyManager),  
      isUserTurn(true), 
      gameOver(false), 
      roundNumber(1) {}

void GameState::reset(ShipManager& userManager, ShipManager& enemyManager) {
    userField = GameField(userField.getWidth(), userField.getHeight(), userManager);
    enemyField = GameField(enemyField.getWidth(), enemyField.getHeight(), enemyManager);
    abilityManager = AbilityManager(); 
    isUserTurn = true;
    gameOver = false;
    placeUserShips();
    placeEnemyShips();
    roundNumber = 1;
}

void GameState::toggleTurn() {
    isUserTurn = !isUserTurn;
}

void GameState::applyAbility() {
    int x, y;
    std::cout << "Enter the coordinates to apply ability (row and column): ";
    std::cin >> x >> y;

    InfoHolder infoHolder(enemyField, enemyManager, x, y);
    
    abilityManager.applyAbility(infoHolder);
}


void GameState::enemyAttack() {
    static bool isSeeded = false;
    if (!isSeeded) {
        srand(static_cast<unsigned int>(time(0)));
        isSeeded = true;
    }

    int x = rand() % userField.getWidth();
    int y = rand() % userField.getHeight();

    std::cout << "Enemy attacks at (" << x << ", " << y << ")\n";
    userField.attackCell(x, y, false);

    if (userField.allShipsDestroyed()) {
        setGameOver(true); 
    }
}


void GameState::attackEnemy(int x, int y) {
    enemyField.attackCell(x, y, false);

    if (enemyField.allShipsDestroyed()) {
        setGameOver(true); 
    }
}

void GameState::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Failed to open file for saving.");
    }

    outFile.write(reinterpret_cast<const char*>(&roundNumber), sizeof(roundNumber));
    outFile.write(reinterpret_cast<const char*>(&isUserTurn), sizeof(isUserTurn));
    outFile.write(reinterpret_cast<const char*>(&gameOver), sizeof(gameOver));

    userField.saveToFile(outFile);
    enemyField.saveToFile(outFile);
    abilityManager.saveToFile(outFile);
}

GameState GameState::loadFromFile(const std::string& filename, ShipManager& userManager, ShipManager& enemyManager) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Failed to open file for loading.");
    }

    GameState gameState(10, 10, userManager, enemyManager); 
    inFile.read(reinterpret_cast<char*>(&gameState.roundNumber), sizeof(gameState.roundNumber));
    inFile.read(reinterpret_cast<char*>(&gameState.isUserTurn), sizeof(gameState.isUserTurn));
    inFile.read(reinterpret_cast<char*>(&gameState.gameOver), sizeof(gameState.gameOver));

    gameState.userField.loadFromFile(inFile);
    gameState.enemyField.loadFromFile(inFile);
    gameState.abilityManager.loadFromFile(inFile);

    return gameState;
}

void GameState::setGameOver(bool isGameOver) {
        gameOver = isGameOver;
    }

bool GameState::isGameOver() const {
    return gameOver;
}

bool GameState::getUserTurn() const {
    return isUserTurn;
}

int GameState::getRoundNumber() const {
    return roundNumber;
}

const GameField& GameState::getUserField() const {
    return userField;
}

const GameField& GameState::getEnemyField() const {
    return enemyField;
}

void GameState::incrementRound() {
    ++roundNumber; 
}

void GameState::placeUserShips() {
    std::cout << "Place your ships on the battlefield:\n";

    for (int i = 0; i < userManager.getAllShips().size(); ++i) {
        Ship& ship = userManager.getShip(i);
        int x, y;
        bool vertical;

        std::cout << "Place ship of size " << ship.getLength() << " (ID: " << i + 1 << "):\n";

        std::cout << "Vertical (1) or Horizontal (0): ";
        std::cin >> vertical;

        bool validPlacement = false;
        while (!validPlacement) {
            std::cout << "Enter coordinates for the ship (x y): ";
            std::cin >> x >> y;

            try {
                validPlacement = userField.placeShip(i, x, y, vertical);  
            } catch (const InvalidShipPlacementException&) {
                std::cout << "Invalid placement, try again.\n";
            }
        }
    }
}

void GameState::placeEnemyShips() {
    std::cout << "Placing enemy ships...\n";

    for (int i = 0; i < enemyManager.getAllShips().size(); ++i) {
        Ship& ship = enemyManager.getShip(i);
        int x, y;
        bool vertical;

        vertical = rand() % 2;  

        bool validPlacement = false;
        while (!validPlacement) {
            x = rand() % enemyField.getWidth();
            y = rand() % enemyField.getHeight();

            try {
                validPlacement = enemyField.placeShip(i, x, y, vertical);  
            } catch (const InvalidShipPlacementException&) {
            }
        }
    }

    std::cout << "Enemy ships have been placed.\n";
}

std::ostream& operator<<(std::ostream& os, const GameState& gameState) {
    os << "Round: " << gameState.roundNumber << "\n";
    os << "Turn: " << (gameState.isUserTurn ? "Player's" : "Enemy's") << "\n";
    os << "Game Over: " << (gameState.gameOver ? "Yes" : "No") << "\n";
    gameState.userField.display(false);
    gameState.enemyField.display(true);
    return os;
}

std::istream& operator>>(std::istream& is, GameState& gameState) {
    is >> gameState.roundNumber;
    is >> gameState.isUserTurn;
    is >> gameState.gameOver;

    gameState.userField.loadFromStream(is);
    gameState.enemyField.loadFromStream(is);
    gameState.abilityManager.loadFromStream(is);

    return is;
}



#include "Game.h"
#include <stdexcept>

Game::Game(ShipManager& userManager, ShipManager& enemyManager)
        : userManager(userManager), enemyManager(enemyManager),
          gameState(10, 10, userManager, enemyManager), 
          isRunning(false) {}

void Game::startNewGame() {
    gameState.reset(userManager, enemyManager);  
    isRunning = true;
    std::cout << "New game started!\n";
}

void Game::endGame() {
    if (gameState.isGameOver()) {
        bool userWon = !gameState.getUserField().allShipsDestroyed(); 
        if (userWon) {
            std::cout << "You won the round!\n";
            startNewRound(); 
        } else {
            std::cout << "You lost the game. Try again.\n";
        }
        isRunning = false; 
    }
}

void Game::startNewRound() {
    gameState.incrementRound();  
    gameState.reset(userManager, enemyManager);  
    std::cout << "New round started!\n";
    isRunning = true;  
}

void Game::makeMove() {
    if (gameState.getUserTurn()) {
        playerTurn();
    } else {
        enemyTurn();
    }
}

void Game::playerTurn() {
    std::cout << "Your turn.\n";
    
    std::cout << "Do you want to use a special ability? (y/n): ";
    char choice;
    std::cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        gameState.applyAbility(); 
    }
    int row, col;
    std::cout << "Enter row and column to attack: ";
    std::cin >> row >> col;

    try {
        gameState.attackEnemy(row, col);  
        std::cout << "Attack successful!\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Invalid coordinates! Try again.\n";
        return;
    }

    gameState.toggleTurn();
}

void Game::enemyTurn() {
    std::cout << "Enemy's turn.\n";
    
    gameState.enemyAttack();
    std::cout << "Enemy attacked your field!\n";

    gameState.toggleTurn();
}

void Game::saveGame(const std::string& filename) {
    try {
        gameState.saveToFile(filename);
        std::cout << "Game saved successfully.\n";
    } catch (const std::exception& e) {
        std::cout << "Failed to save the game: " << e.what() << std::endl;
    }
}

void Game::loadGame(const std::string& filename) {
    try {
        gameState.loadFromFile(filename, userManager, enemyManager);
        std::cout << "Game loaded successfully.\n";
    } catch (const std::exception& e) {
        std::cout << "Failed to load the game: " << e.what() << std::endl;
    }
}

bool Game::isGameRunning() const {
    return isRunning;
}

const GameState& Game::getGameState() const {
    return gameState;
}

void Game::displayGameState() const {
    std::cout << "Round: " << gameState.getRoundNumber() << std::endl;
    std::cout << (gameState.getUserTurn() ? "Your turn." : "Enemy's turn.") << std::endl;

    std::cout << "\nYour Field:\n";
    gameState.getUserField().display(false);

    std::cout << "\nEnemy Field:\n";
    gameState.getEnemyField().display(true);
}


void Game::run() {
    startNewGame();

    while (isRunning) {
        displayGameState();  

        makeMove();  

        endGame();

        std::cout << "Do you want to save the game? (y/n): ";
        char saveChoice;
        std::cin >> saveChoice;

        if (saveChoice == 'y' || saveChoice == 'Y') {
            std::cout << "Enter save file name: ";
            std::string saveFileName;
            std::cin >> saveFileName;
            saveGame(saveFileName);  
        }
    }
}
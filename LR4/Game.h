#pragma once

#include "GameState.h"
#include "ShipManager.h"
#include <iostream>

class Game {
private:
    GameState gameState;
    ShipManager& userManager;  
    ShipManager& enemyManager;
    bool isRunning;

public:
    Game(ShipManager& userManager, ShipManager& enemyManager); 

    void startNewGame();
    void endGame();
    void makeMove();
    void playerTurn();
    void enemyTurn();

    void saveGame(const std::string& filename);
    void loadGame(const std::string& filename);

    bool isGameRunning() const;
    const GameState& getGameState() const;
    void startNewRound();
    void displayGameState() const;
    void run();
};

#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>  
#include <ctime>  
#include "GameField.h"
#include "InfoHolder.h"
#include "AbilityManager.h"
#include "ShipManager.h"

class GameState {
private:
    GameField userField; 
    GameField enemyField;
    AbilityManager abilityManager; 
    ShipManager& userManager;
    ShipManager& enemyManager;
    bool isUserTurn;
    bool gameOver; 
    int roundNumber; 

public:
    GameState(int fieldWidth, int fieldHeight, ShipManager& userManager, ShipManager& enemyManager);

    void reset(ShipManager& userManager, ShipManager& enemyManager); 
    void toggleTurn();
    void applyAbility(); 
    void enemyAttack(); 
    void attackEnemy(int x, int y); 

    void saveToFile(const std::string& filename) const;
    static GameState loadFromFile(const std::string& filename, ShipManager& userManager, ShipManager& enemyManager);

    void setGameOver(bool isGameOver);
    bool isGameOver() const;
    bool getUserTurn() const;
    void incrementRound();
    int getRoundNumber() const;
    const GameField& getUserField() const;
    const GameField& getEnemyField() const;

    void placeUserShips();
    void placeEnemyShips(); 

    friend std::ostream& operator<<(std::ostream& os, const GameState& gameState);
    friend std::istream& operator>>(std::istream& is, GameState& gameState);
};




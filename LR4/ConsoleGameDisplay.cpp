#include "ConsoleGameDisplay.h"
#include <iostream>

void ConsoleGameDisplay::display(const GameState& state) {
    std::cout << "Round: " << state.getRoundNumber() << std::endl;
    std::cout << "User's Turn: " << (state.getUserTurn() ? "Yes" : "No") << std::endl;
    state.getUserField().display(false); 
    state.getEnemyField().display(true);  
}

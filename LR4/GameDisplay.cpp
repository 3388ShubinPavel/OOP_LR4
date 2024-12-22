#include "GameDisplay.h"

template class GameDisplay<ConsoleGameDisplay>;

template <typename DisplayStrategy>
GameDisplay<DisplayStrategy>::GameDisplay(Game& game, DisplayStrategy& strategy)
    : game(game), strategy(strategy) {}

template <typename DisplayStrategy>
void GameDisplay<DisplayStrategy>::updateDisplay() {
    strategy.display(game.getGameState());
}

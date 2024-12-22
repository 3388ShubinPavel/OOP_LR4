#pragma once
#include "Game.h"
#include "ConsoleGameDisplay.h"

template <typename DisplayStrategy>
class GameDisplay {
public:
    GameDisplay(Game& game, DisplayStrategy& strategy);

    void updateDisplay();

private:
    Game& game;
    DisplayStrategy& strategy;
};

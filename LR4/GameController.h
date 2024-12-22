#pragma once
#include <memory>
#include <functional>
#include "Game.h"
#include "TerminalCommandHandler.h"

template <typename CommandHandler>
class GameController {
public:
    GameController(Game& game, CommandHandler& handler);

    void processCommand(char input);

private:
    Game& game;
    CommandHandler& handler;
};

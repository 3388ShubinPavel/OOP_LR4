#pragma once
#include <iostream>
#include <map>
#include <functional>
#include "Game.h"

class TerminalCommandHandler {
public:
    TerminalCommandHandler(Game& game);

    std::function<void()> getCommand(char input);

private:
    std::map<char, std::function<void()>> commandMap;
};

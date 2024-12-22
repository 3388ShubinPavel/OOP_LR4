#include "TerminalCommandHandler.h"

TerminalCommandHandler::TerminalCommandHandler(Game& game) {
    commandMap = {
        {'start', [&]() { game.startNewGame(); }},
        {'load', [&]() { game.loadGame("savefile.dat"); }},
        {'end', [&]() { game.endGame(); }},
        {'makemove', [&]() { game.makeMove(); }},
        {'save', [&]() { game.saveGame("savefile.dat"); }}
    };
}

std::function<void()> TerminalCommandHandler::getCommand(char input) {
    if (commandMap.find(input) != commandMap.end()) {
        return commandMap[input];
    }
    return nullptr;  
}

#include "GameController.h"

template class GameController<TerminalCommandHandler>;

template <typename CommandHandler>
GameController<CommandHandler>::GameController(Game& game, CommandHandler& handler)
    : game(game), handler(handler) {}

template <typename CommandHandler>
void GameController<CommandHandler>::processCommand(char input) {
    auto command = handler.getCommand(input);
    if (command) {
        command();
    } else {
        std::cout << "Invalid command!" << std::endl;
    }
}

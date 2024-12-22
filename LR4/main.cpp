#include <iostream>
#include "Game.h"
#include "GameController.h"
#include "GameDisplay.h"
#include "ConsoleGameDisplay.h"
#include "TerminalCommandHandler.h"

int main() {
    std::vector<int> userShipSizes = {4, 3, 2, 1};  
    std::vector<int> enemyShipSizes = {4, 3, 2, 1}; 

    ShipManager userManager(userShipSizes.size(), userShipSizes);
    ShipManager enemyManager(enemyShipSizes.size(), enemyShipSizes);

    Game game(userManager, enemyManager);

    ConsoleGameDisplay displayStrategy;
    GameDisplay<ConsoleGameDisplay> gameDisplay(game, displayStrategy);

    TerminalCommandHandler commandHandler(game);
    GameController<TerminalCommandHandler> gameController(game, commandHandler);

    while (true) {
        std::cout << "Welcome to Battleship!\n";
        std::cout << "1. Start New Game\n";
        std::cout << "2. Load Game\n";
        std::cout << "3. Exit\n";
        std::cout << "Select an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Starting a new game...\n";
                game.run();  
                break;
            }
            case 2: {
                std::cout << "Enter the filename to load the game: ";
                std::string filename;
                std::cin >> filename;

                try {
                    game.loadGame(filename);
                    std::cout << "Game loaded successfully.\n";
                    bool isRunning = true;
                    while (isRunning) {
                        gameDisplay.updateDisplay();

                        char command;
                        std::cout << "Enter command: ";
                        std::cin >> command;
                        gameController.processCommand(command);

                        game.endGame();

                        std::cout << "Do you want to save the game? (y/n): ";
                        char saveChoice;
                        std::cin >> saveChoice;

                        if (saveChoice == 'y' || saveChoice == 'Y') {
                            std::cout << "Enter save file name: ";
                            std::string saveFileName;
                            std::cin >> saveFileName;
                            game.saveGame(saveFileName);  
                        }
                    }
                } catch (const std::exception& e) {
                    std::cout << "Error loading game: " << e.what() << "\n";
                }
                break;
            }
            case 3:
                std::cout << "Exiting the game. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

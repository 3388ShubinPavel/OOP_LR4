#include "Scanner.h"
#include <iostream>

void Scanner::apply(InfoHolder& infoHolder) {
    int fieldHeight = infoHolder.gameField.getHeight();
    int fieldWidth = infoHolder.gameField.getWidth();
    
    if (infoHolder.startRow < 0 || infoHolder.startCol < 0 || infoHolder.startRow >= fieldWidth - 1 || infoHolder.startCol >= fieldHeight - 1) {
        std::cerr << "Error: Coordinates are out of bounds!" << std::endl;
        return;
    }

    bool segmentFound = false;

    for (int i = infoHolder.startRow; i < infoHolder.startRow + 2; ++i) {
        for (int j = infoHolder.startCol; j < infoHolder.startCol + 2; ++j) {
            Cell& cell = infoHolder.gameField.getCell(i,j);
            if (cell.getStatus() == CellStatus::Ship || cell.getStatus()==CellStatus::Damaged) {
                segmentFound = true;
                std::cout << "Ship found at cell [" << i << "][" << j << "]\n";
            }
        }
    }

    if (!segmentFound) {
        std::cout << "No ships found in the 2x2 area.\n";
    }
}


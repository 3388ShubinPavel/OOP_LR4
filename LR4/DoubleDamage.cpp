#include "DoubleDamage.h"
#include <iostream>

void DoubleDamageAbility::apply(InfoHolder& infoHolder) {
    Cell& targetCell = infoHolder.gameField.getCell(infoHolder.startRow, infoHolder.startCol);
    targetCell.attack(true);
    //std::cout << "Double damage applied at (" << startRow << ", " << startCol << ")" << std::endl;
}


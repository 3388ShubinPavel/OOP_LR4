#pragma once

#include "GameField.h"
#include "ShipManager.h"

class GameField;
class ShipManager;

class InfoHolder{
    public:
        GameField& gameField;
        ShipManager& shipManager;
        int startRow;
        int startCol;
        InfoHolder(GameField& gameField, ShipManager& shipManager, int startRow = 0, int startCol = 0):
            gameField(gameField), shipManager(shipManager), startRow(startRow),startCol(startCol){}
};
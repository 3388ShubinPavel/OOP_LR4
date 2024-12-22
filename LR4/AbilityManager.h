#pragma once

#include <queue>
#include <memory>
#include <vector>
#include <fstream>
#include "Ability.h"
#include "Bombardment.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "NoAbilitiesException.h"
#include "InfoHolder.h"

class Ability;

class AbilityManager {
public:
    AbilityManager();

    void addAbility(std::shared_ptr<Ability> ability);

    void applyAbility(InfoHolder& infoHolder);

    void grantRandomAbility();

    void saveToFile(std::ofstream& outFile) const;
    void loadFromFile(std::ifstream& inFile) ;
    void loadFromStream(std::istream& inStream);

private:
    std::queue<std::shared_ptr<Ability>> abilitiesQueue;
    std::vector<std::shared_ptr<Ability>> allAbilities;
};

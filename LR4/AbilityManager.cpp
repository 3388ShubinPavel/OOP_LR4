#include "AbilityManager.h"
#include <cstdlib>
#include <ctime>

AbilityManager::AbilityManager() {
    allAbilities.push_back(std::make_shared<BombardmentAbility>());
    allAbilities.push_back(std::make_shared<DoubleDamageAbility>());
    allAbilities.push_back(std::make_shared<Scanner>());

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<std::shared_ptr<Ability>> tempAbilities = allAbilities;

    while (!tempAbilities.empty()) {
        int randomIndex = std::rand() % tempAbilities.size();
        abilitiesQueue.push(tempAbilities[randomIndex]);
        
        tempAbilities.erase(tempAbilities.begin() + randomIndex);
    }

    // std::srand(std::time(nullptr));
    // int initialAbilityIndex = std::rand() % allAbilities.size();
    // abilitiesQueue.push(allAbilities[initialAbilityIndex]);
}

void AbilityManager::addAbility(std::shared_ptr<Ability> ability) {
    abilitiesQueue.push(ability);
}

void AbilityManager::applyAbility(InfoHolder& infoHolder) {
    if (abilitiesQueue.empty()) {
        throw NoAbilitiesException();
    }

    auto ability = abilitiesQueue.front();
    abilitiesQueue.pop();
    ability->apply(infoHolder);

}

void AbilityManager::grantRandomAbility() {
    int randomIndex = std::rand() % allAbilities.size();
    addAbility(allAbilities[randomIndex]);
    std::cout << "Granted new ability: " << std::endl;
}

void AbilityManager::saveToFile(std::ofstream& outFile) const {
    size_t queueSize = abilitiesQueue.size();
    outFile.write(reinterpret_cast<const char*>(&queueSize), sizeof(queueSize));

    // Сохраняем типы способностей в стеке
    std::queue<std::shared_ptr<Ability>> tempQueue = abilitiesQueue;
    while (!tempQueue.empty()) {
        AbilityType abilityType = tempQueue.front()->getType();
        outFile.write(reinterpret_cast<const char*>(&abilityType), sizeof(abilityType));
        tempQueue.pop();
    }
}

void AbilityManager::loadFromFile(std::ifstream& inFile) {
    size_t queueSize;
    inFile.read(reinterpret_cast<char*>(&queueSize), sizeof(queueSize));

    for (size_t i = 0; i < queueSize; ++i) {
        AbilityType abilityType;
        inFile.read(reinterpret_cast<char*>(&abilityType), sizeof(abilityType));

        std::shared_ptr<Ability> ability;
        if (abilityType == AbilityType::Bombardment) {
            ability = std::make_shared<BombardmentAbility>();
        } else if (abilityType == AbilityType::DoubleDamage) {
            ability = std::make_shared<DoubleDamageAbility>();
        } else if (abilityType == AbilityType::Scanner) {
            ability = std::make_shared<Scanner>();
        }

        abilitiesQueue.push(ability);  
    }
}

void AbilityManager::loadFromStream(std::istream& inStream) {
    if (!inStream) {
        throw std::runtime_error("Failed to read from stream");
    }

    size_t queueSize;
    inStream.read(reinterpret_cast<char*>(&queueSize), sizeof(queueSize));

    for (size_t i = 0; i < queueSize; ++i) {
        AbilityType abilityType;
        inStream.read(reinterpret_cast<char*>(&abilityType), sizeof(abilityType));

        std::shared_ptr<Ability> ability;

        // Создание способности на основе типа
        switch (abilityType) {
            case AbilityType::Bombardment:
                ability = std::make_shared<BombardmentAbility>();
                break;
            case AbilityType::DoubleDamage:
                ability = std::make_shared<DoubleDamageAbility>();
                break;
            case AbilityType::Scanner:
                ability = std::make_shared<Scanner>();
                break;
            default:
                throw std::runtime_error("Unknown ability type in stream");
        }

        abilitiesQueue.push(ability);
    }
}

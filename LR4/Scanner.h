#pragma once

#include "InfoHolder.h"
#include "Ability.h"
#include <vector>

class Scanner : public Ability {
public:
    void apply(InfoHolder& infoHolder) override;

    AbilityType getType() const override {
        return AbilityType::Scanner;
    }
};

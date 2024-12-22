#pragma once

#include "InfoHolder.h"
#include "Ability.h"
#include <string>

class DoubleDamageAbility : public Ability {
public:
    void apply(InfoHolder& infoHolder) override;

    AbilityType getType() const override {
        return AbilityType::DoubleDamage;
    }
};

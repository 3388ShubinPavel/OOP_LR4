#pragma once
#include <iostream>
#include <string>
#include "InfoHolder.h"

class InfoHolder;

enum class AbilityType {
    Bombardment,
    DoubleDamage,
    Scanner
};

class Ability {
public:
    virtual ~Ability() = default;
    virtual void apply(InfoHolder& infoHolder) = 0;
    virtual AbilityType getType() const = 0;
};

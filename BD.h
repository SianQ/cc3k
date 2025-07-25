#pragma once
#include "Decorator.h"
#include "Potion.h"

class BoostDefDecorator : public CharacterDecorator {
    int boost;
public:
    BoostDefDecorator(std::shared_ptr<Character> base, int amount);
    int getDef() const override;
    PotionType getType() const override;
    std::string getName() const override;
};

#pragma once
#include "Decorator.h"
#include <memory>
#include "Potion.h"

class BoostAtkDecorator : public CharacterDecorator {
    int boost;
public:
    BoostAtkDecorator(std::shared_ptr<Character> base, int amount);
    int getAtk() const override;
    PotionType getType() const override;
};

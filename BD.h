#pragma once
#include "Decorator.h"

class BoostDefDecorator : public CharacterDecorator {
    int boost;
public:
    BoostDefDecorator(std::shared_ptr<Character> base, int amount);
    int getDef() const override;
};
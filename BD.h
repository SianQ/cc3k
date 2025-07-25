#pragma once
#include "Character.h"
#include "Decorator.h"
#include "Potion.h"

class BoostDefDecorator : public Decorator {
    int boost;
public:
    BoostDefDecorator(Character* base, int amount = 5);
    int getDef() const override;
};

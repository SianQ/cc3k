#pragma once
#include "Character.h"
#include "Decorator.h"
#include "Potion.h"

class BoostAtkDecorator : public Decorator {
    int boost;
public:
    BoostAtkDecorator(Character* base, int amount = 5);
    int getAtk() const override;
};

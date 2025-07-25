#pragma once
#include "Character.h"
#include "Decorator.h"
#include "Potion.h"

class BoostDefDecorator : public Decorator {
    int boost;
public:
    BoostDefDecorator(std::shared_ptr<Player> next, int amount = 5);
    int getDef() const override;
};

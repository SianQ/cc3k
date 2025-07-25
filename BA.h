#pragma once
#include "Character.h"
#include "Decorator.h"
#include "Player.h"
#include "Potion.h"

class BoostAtkDecorator : public Decorator {
    int boost;
public:
    BoostAtkDecorator(std::shared_ptr<Player> next, int amount = 5);
    int getAtk() const override;
};

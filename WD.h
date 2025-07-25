#pragma once
#include "Player.h"
#include "Decorator.h"

class WoundDefDecorator : public Decorator {
    int penalty;
public:
    WoundDefDecorator(std::shared_ptr<Player> next, int amount = 5);
    int getDef() const override;
};

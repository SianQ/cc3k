#pragma once
#include "Character.h"
#include "Decorator.h"
#include <algorithm>

class RHDecorator : public Decorator {
public:
    RHDecorator(std::shared_ptr<Player> next);
    int getHP() const override;
    bool isPlayer() const override;
};

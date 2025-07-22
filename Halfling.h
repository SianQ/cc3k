// Halfling.h
#pragma once

#include "Enemy.h"
#include <vector>

/**
 * Halfling: has a 50% chance to dodge player attacks
 */
class Halfling : public Enemy {
public:
    Halfling(int x, int y);

    void act(Level &level, Player &pc) override;
    std::vector<Item*> dropLoot() const override;
};

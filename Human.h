// Human.h
#pragma once

#include "Enemy.h"
#include <vector>

/**
 * Human: drops two piles of normal gold
 */
class Human : public Enemy {
public:
    Human(int x, int y);

    // Enemy behavior on its turn
    void act(Level &level, Player &pc) override;

    // Loot dropped on death
    std::vector<Item*> dropLoot() const override;
};

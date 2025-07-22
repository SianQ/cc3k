// Orc.h
#pragma once

#include "Enemy.h"
#include <vector>

/**
 * Orc: deals 1.5× damage when attacking Goblin
 */
class Orc : public Enemy {
public:
    Orc(int x, int y);

    void act(Level &level, Player &pc) override;
    std::vector<Item*> dropLoot() const override;
};

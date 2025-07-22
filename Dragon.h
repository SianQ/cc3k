// Dragon.h
#pragma once

#include "Enemy.h"
#include <vector>

/**
 * Dragon: never moves, always hostile,
 * guards its treasure hoard
 */
class Dragon : public Enemy {
public:
    Dragon(int x, int y);

    void act(Level &level, Player &pc) override;
    std::vector<Item*> dropLoot() const override;
};

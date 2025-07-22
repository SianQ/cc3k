// Merchant.h
#pragma once

#include "Enemy.h"
#include <vector>

/**
 * Merchant: starts neutral; if attacked, becomes hostile globally.
 * Drops one pile of merchant gold.
 */
class Merchant : public Enemy {
public:
    Merchant(int x, int y);

    void act(Level &level, Player &pc) override;
    std::vector<Item*> dropLoot() const override;
};

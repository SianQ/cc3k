// Dwarf.h
#pragma once

#include "Enemy.h"
#include <vector>

/**
 * Dwarf: special interaction when attacked by Vampire,
 * drops one pile of normal gold
 */
class Dwarf : public Enemy {
public:
    Dwarf(int x, int y);

    void act(Level &level, Player &pc) override;
    std::vector<Item*> dropLoot() const override;
};

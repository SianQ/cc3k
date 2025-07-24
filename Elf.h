// Elf.h
#pragma once

#include "Enemy.h"
#include <vector>

/**
 * Elf: attacks twice in one turn when attacking non-Drow characters
 */
class Elf : public Enemy {
public:
    Elf(int x, int y);

    void act(Level &level, Player &pc) override;
    std::vector<Item*> dropLoot() const override;
    
};

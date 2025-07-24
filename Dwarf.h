#pragma once
#include "Enemy.h"

/**
 * Dwarf: HP=100, Atk=20, Def=30.
 * Drops one pile of 2 gold.
 */
class Dwarf : public Enemy {
public:
    Dwarf(int row, int col);

    void act(Map& map, Player& pc) override;
    void attack(Player& pc) override;
    std::vector<Item*> dropLoot() const override;
    
};

#pragma once
#include "Enemy.h"

/**
 * Dragon: HP=150, Atk=20, Def=20.
 * Stationary; guards a hoard placed on map.
 */
class Dragon : public Enemy {
public:
    Dragon(int row, int col);

    void act(Map &map, Player &pc) override;
    void attack(Player &pc) override;
    std::vector<Item*> dropLoot() const override;
};

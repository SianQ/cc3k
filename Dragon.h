#pragma once
#include "Enemy.h"

/**
 * Dragon: HP=150, Atk=20, Def=20.
 * Stationary; guards a hoard placed on map.
 */
class Dragon : public Enemy {
    Tile* hoard;
public:
    Dragon();
    void setHoard(Tile* tile);
    void act(Map &map, Player &pc) override;
    void attack(Player &pc) override;
    void dropLoot(Level& level, Map& map) const override;
};

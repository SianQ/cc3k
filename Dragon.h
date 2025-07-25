#pragma once
#include "Character.h"
#include "Enemy.h"
#include "Level.h"
#include "Map.h"
#include "Tile.h"

/**
 * Dragon: HP=150, Atk=20, Def=20.
 * Stationary; guards a hoard placed on map.
 */
class Dragon : public Enemy {
    Tile* hoard;
public:
    Dragon();
    void setHoard(Tile* tile);
    void act(Map &map, Player &pc, Level &level) override;
    void attack(Player &pc, bool isAttackSuccessful) override;
    int beAttackedBy(Character* attacker) override;
};

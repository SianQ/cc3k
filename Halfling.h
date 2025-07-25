#pragma once
#include "Enemy.h"

/**
 * Halfling: HP=100, Atk=15, Def=20.
 * When attacked by player, 50% chance to evade.
 * Drops one pile of 2 gold.
 */
class Halfling : public Enemy {
public:
    Halfling();

    void act(Map& map, Player& pc) override;
    void attack(Player& pc) override;
    void dropLoot(Level& level, Map& map) const override;
    void beAttackedBy(Character* attacker) override;
};

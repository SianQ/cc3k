#pragma once
#include "Enemy.h"

/**
 * Human: HP=140, Atk=20, Def=20.
 * Drops two piles of 2 gold each.
 */
class Human : public Enemy {
public:
    Human();
    void dropLoot(Level& level, Map& map) const override;
};

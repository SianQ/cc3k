#pragma once
#include "Enemy.h"

/**
 * Orc: HP=180, Atk=30, Def=25.
 * Deals 1.5× damage to Goblin players.
 * Drops one pile of 2 gold.
 */
class Orc : public Enemy {
public:
    Orc();
};

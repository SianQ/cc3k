#pragma once
#include "Enemy.h"

/**
 * Elf: HP=140, Atk=30, Def=10.
 * Attacks twice per turn except against Drow.
 * Drops one pile of 2 gold.
 */
class Elf : public Enemy {
public:
    Elf();

    void attack(Player& pc, bool isAttackSuccessful) override;    
};

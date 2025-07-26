export module Elf;

// import Enemy;

// export

import Enemy;
import LevelFwd;
import Player;

/**
 * Elf: HP=140, Atk=30, Def=10.
 * Attacks twice per turn except against Drow.
 * Drops one pile of 2 gold.
 */
export class Elf : public Enemy {
public:
    Elf();
    void attack(Player& pc, bool isAttackSuccessful, Level& level) override;    
};

#include "Elf.h"
#include "Player.h"
#include <cstdlib>

Elf::Elf()
  : Enemy(140,30,10,"E",true,false) {}

void Elf::attack(Player& pc, bool isAttackSuccessful) {
    if (isAttackSuccessful) {
        pc.beAttackedBy(this);
        if(!pc.isDead() && pc.getRace()!="Drow") {
            pc.beAttackedBy(this);
        }
    }
}

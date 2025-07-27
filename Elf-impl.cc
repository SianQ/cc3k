module Elf;
import Player;
import Level;
import <cstdlib>;

Elf::Elf()
  : Enemy(140,30,10,"E",true,false) {}

void Elf::attack(Player& pc, bool isAttackSuccessful, Level& level) {
    if (isAttackSuccessful) {
        int damage1 = pc.beAttackedBy(this);
        if (damage1 > 0) {
            level.appendMessage("E deals " + std::to_string(damage1) + " damage to PC.");
        }
        
        if(!pc.isDead() && pc.getRace()!="Drow") {
            int damage2 = pc.beAttackedBy(this);
            if (damage2 > 0) {
                level.appendMessage("E deals " + std::to_string(damage2) + " damage to PC.");
            }
        }
    } else {
        level.appendMessage("E misses PC.");
    }
}

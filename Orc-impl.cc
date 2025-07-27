module Orc;

import Race;
import Enemy;

Orc::Orc()
  : Enemy(Race::Orc, 180,30,25) {}

int Orc::attack(Character* target, bool isSuccess) {
    if (!isSuccess) { return 0; }
    int damage = 1.5 * Character::calculateDamage(getAtk(), target->getDef());
    target->takeDamage(damage, this);
    return damage;    
}

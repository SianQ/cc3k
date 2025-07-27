module Orc;

import Race;

Orc::Orc()
  : Enemy(Race::Orc, 180,30,25) {}

int Orc::attack(const Character* target, bool isSuccess) {
    if (!isSuccess) { return 0; }
    int damage = 1.5 * Character::calculateDamage(atk, target->getDef());
    target->takeDamage(damage, this, true);
    return damage;    
}

module Goblin;

import Race;

Goblin::Goblin()
    : Player(Race::Goblin, 110,15,20) {}

int Goblin::attack(Character* target, bool isSuccess) {
    if (target == nullptr || (target->getRace() == Race::Halfling && !isSuccess)) { return 0; }
    int damage = calculateDamage(getAtk(), target->getDef());
    target->takeDamage(damage, this);
    if (target->isDead()) { gold += 5; }
    return damage;
}
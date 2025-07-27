module Vampire;

Vampire::Vampire()
  : Player(50,25,25,50,"Vampire") {}

Vampire::~Vampire() {}

int Vampire::attack(const Character* target) {
    if (target == nullptr) {
        return 0;
    }
    
    int damage = calculateDamage(getAtk(), target->getDef());
    target->takeDamage(damage, this);
    
    if (damage > 0) { setHp(getHp() + 5); }
    
    return damage;
}

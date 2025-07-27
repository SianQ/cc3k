module Vampire;

Vampire::Vampire()
  : Player(50,25,25,50,"Vampire") {}

Vampire::~Vampire() = default;

int Vampire::attack(const Character* target, bool isSuccess) {
    if (target == nullptr || (target->getRace == Race::Halfling && !isSuccess)) { return 0; }
    
    int damage = calculateDamage(getAtk(), target->getDef());
    target->takeDamage(damage, this);
    
    if (target->getRace() == Race::Dwarf ) {
        setHp(std::min(getHp() - 5, 0));
    } else if (damage > 0) { 
        setHp(getHp() + 5);
    }
    return damage;
}

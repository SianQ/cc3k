module Goblin;

Goblin::Goblin()
    : Player(110,15,20,110,"Goblin") {}

Goblin::~Goblin() = default;

int Goblin::attack(const Character* target) {
    if (target->isDead()) return 0;
    int damage = calculateDamage(getAtk(), target->getDef());
    target->takeDamage(damage, this);
    if (target->isDead()) { gold += 5; }
    return damage;
}
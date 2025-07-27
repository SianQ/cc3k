module Merchant;
import Race;

Merchant::Merchant()
  : Enemy(Race::Merchant, 30,70,5) {}

bool Merchant::isHostile() {
    return hostileAll;
}

void Merchant::setHostile(bool isHostile) {
    hostileAll = isHostile;
}

void Merchant::takeDamage(int damage, const Character* source) {
    setHostile(true);
    Enemy::takeDamage(damage, source);
}

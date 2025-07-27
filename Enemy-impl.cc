module Enemy;

import Race;
import <cstdlib>;
import <utility>;

Enemy::Enemy(Race race, int hp, int atk, int def)
  : Character(race, hp, atk, def)
{
    if (race == Race::Merchant) {
        hostile = false;
    }
}

int Enemy::attack(const Character* target, bool isSuccess) {
    if (!isSuccess) { return 0; }
    int damage = Character::calculateDamage(atk, target->getDef());
    target->takeDamage(damage, this, true);
    return damage;
}

void Enemy::takeDamage(int damage, const Character* source) {
    hp -= damage;
    if (hp <= 0) {
        hp = 0;
    }
}

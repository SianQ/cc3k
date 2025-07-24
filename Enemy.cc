#include "Enemy.h"
#include "Potion.h"

Enemy::Enemy(int hp_, int atk_, int def_,
             int row, int col,
             const std::string& typeSymbol,
             bool hostile_, bool isDragon_)
  : Character(hp_, atk_, def_, row, col),
    hostile(hostile_), isDragon(isDragon_), type(typeSymbol) {}

void Enemy::usePotion(Potion* /*pot*/) {
    // Default: enemies ignore potions
}

bool Enemy::isHostile() const {
    return hostile;
}

void Enemy::setHostile(bool h) {
    hostile = h;
}

bool Enemy::dragon() const {
    return isDragon;
}

const std::string& Enemy::getSymbol() const {
    return type;
}

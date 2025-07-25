#include "Enemy.h"
#include "Potion.h"

Enemy::Enemy(int hp_, int atk_, int def_,             
             const std::string& typeSymbol,
             bool hostile_, bool isDragon_,
             int row = -1, int col = -1)
  : Character(hp_, atk_, def_, row, col), // maxHP is not used in this context
    hostile(hostile_), isDragon(isDragon_), type(typeSymbol) {}

bool Enemy::isHostile() const {
    return hostile;
}

void Enemy::setHostile(bool h) {
    hostile = h;
}

bool Enemy::dragon() const {
    return isDragon;
}

char Enemy::getSymbol() const {
    return type[0];
}
std::string Enemy::getRace() const { return race; }

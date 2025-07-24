#include "Character.h"
#include <cmath>
#include <utility>

int Character::getHP() const { return hp; }
int Character::getAtk() const { return atk; }
int Character::getDef() const { return def; }
bool Character::isDead() { return hp <= 0; }
bool Character::isPlayer() const { return false; }

std::pair<int, int> Character::getPosition() const { return {row, col}; }
void Character::setPosition(int r, int c) { row = r; col = c; }

// Shared damage calculation helper (can also be standalone function)
int Character::calculateDamage(int attackerAtk, int defenderDef) {
    return std::ceil((100.0 / (100 + defenderDef)) * attackerAtk);
}


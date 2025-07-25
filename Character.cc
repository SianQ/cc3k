#pragma once
#include "Character.h"
#include <cmath>
#include <utility>

Character::Character(int hp, int atk, int def, int x, int y, int maxHP) : hp{hp}, atk{atk}, def{def}, x{x}, y{y}, maxHP{maxHP} {}
Character::~Character() = default;
int Character::getHP() const { return hp; }
int Character::getAtk() const { return atk; }
int Character::getDef() const { return def; }
bool Character::isDead() { return hp <= 0; }
bool Character::isPlayer() const { return false; }
int Character::getMaxHP() const { return maxHP; }
void Character::setHP(int newHp) { hp = newHp; }
std::pair<int, int> Character::getPosition() const { return {x, y}; }
void Character::setPosition(int r, int c) { x = r; y = c; }
int Character::beAttackedBy(Character* enemy) {
    int dmg = Character::calculateDamage(enemy->getAtk(), this->getDef());
    this->hp = std::max(0, this->hp - dmg);
    return dmg;
}

// Shared damage calculation helper (can also be standalone function)
int Character::calculateDamage(int attackerAtk, int defenderDef) {
    return std::ceil((100.0 / (100 + defenderDef)) * attackerAtk);
}

std::string Character::getRace() const {
    return "";
}

char Character::getSymbol() const {
    return '?';
}

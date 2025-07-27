module Character;
import Race;

import <cmath>;
import <utility>;

Character::Character(Race race, int hp, int atk, int def): 
    race{race}, hp{hp}, atk{atk}, def{def}, maxHP{hp} 
{
    if      (race == Race::Human)     symbol = 'H';
    else if (race == Race::Dwarf)     symbol = 'W';
    else if (race == Race::Elf)       symbol = 'E';
    else if (race == Race::Orc)       symbol = 'O';
    else if (race == Race::Merchant)  symbol = 'M';
    else if (race == Race::Dragon)    symbol = 'D';
    else if (race == Race::Halfling)  symbol = 'L';
    else                              symbol = '@';
}

int Character::getAtk() const { return atk; }
int Character::getDef() const { return def; }
int Character::getHp() const { return hp; }
Race Character::getRace() const { return race; }
char Character::getSymbol() const { return symbol; }
int Character::getMaxHp() const { return maxHP; }
int Character::getX() const { return x; }
int Character::getY() const { return y; }

void Character::setHp(const int newHp) {
    if (race == Race::Vampire) {
        hp = std::max(0, newHp);
    } else {
        hp = std::max(0, newHp);
        if (hp > maxHP) { hp = maxHP; }
    }
}
int Character::setX(const int x) {
    this->x = x;
    return x;
}
int Character::setY(const int y) {
    this->y = y;
    return y;
}

bool Character::isPlayer() const { return false; }
bool Character::isDead() const { return hp <= 0; }

int Character::calculateDamage(int attackerAtk, int defenderDef) {
    return std::ceil((100.0 / (100 + defenderDef)) * attackerAtk);
}

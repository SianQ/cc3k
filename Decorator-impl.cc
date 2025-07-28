module Decorator;

import Player;
import Race;
import <memory>;

Decorator::Decorator(std::shared_ptr<Player> next)
  : Player(
      next->getRace(),
      next->getHp(),
      next->getAtk(),
      next->getDef()
    ),
    next(std::move(next))
{}

int Decorator::getAtk()   const { return next->getAtk(); }
int Decorator::getDef()   const { return next->getDef(); }
int Decorator::getHp()    const { return next->getHp(); }
Race Decorator::getRace() const { return next->getRace(); }
char Decorator::getSymbol()const { return next->getSymbol(); }
int Decorator::getMaxHp() const { return next->getMaxHp(); }
int Decorator::getX()     const { return next->getX(); }
int Decorator::getY()     const { return next->getY(); }

void Decorator::setHp(int newHp)              { next->setHp(newHp); }
int  Decorator::setMaxHp(int newMaxHp)        { return next->setMaxHp(newMaxHp); }
void Decorator::setX(int newX)                { next->setX(newX); }
void Decorator::setY(int newY)                { next->setY(newY); }

bool Decorator::isPlayer() const               { return next->isPlayer(); }
bool Decorator::isDead()   const               { return next->isDead(); }

int  Decorator::attack(Character* t, bool ok)  { return next->attack(t, ok); }
void Decorator::takeDamage(int dmg, const Character* s) { next->takeDamage(dmg, s); }

void Decorator::perTermEvent()                 { next->perTermEvent(); }

int Decorator::calculateDamage(int atk, int def) { return next->calculateDamage(atk, def); }

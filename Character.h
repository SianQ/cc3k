// export module Character;

// import Player;
// import Enemy;
// import Item;

// export
#pragma once
class Player;
#include "Enemy.h"
#include "Item.h"
#include <utility>

class Character {    
protected:
    int hp, atk, def;
    int row, col;

public:
    Character(int hp, int atk, int def, int row, int col);
    virtual ~Character();
    
    virtual int getHp() const;
    virtual int getAtk() const;
    virtual int getDef() const;
    virtual void setPosition(int r, int c);
    virtual std::pair<int, int> getPosition() const;

    virtual void move(int row, int col);
    virtual void takeDamage(Character* enemy);
    virtual bool isDead();
    virtual void pickUp(Item* item);
    virtual void useItem(Item* item);
    virtual void attack(Character* target);
    virtual void beAttackedBy(Character* attacker);
    static int calculateDamage(int atk, int def);
};

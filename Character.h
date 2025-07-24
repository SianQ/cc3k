// export module Character;

// import Player;
// import Enemy;
// import Item;

// export
#pragma once
class Player;
#include "Item.h"
#include <utility>
#include <memory>
#include <algorithm>

class Character {    
protected:
    int hp, atk, def;
    int row, col;

public:
    Character(int hp, int atk, int def, int row, int col);
    virtual ~Character() = default;
    
    // virtual int getAtk() const = 0;
    // virtual int getDef() const = 0;
    // virtual int getHP() const = 0;
    // virtual void setHP(int newHp) = 0;
    virtual void setPosition(int r, int c);
    virtual std::pair<int, int> getPosition() const;

    virtual void move(int row, int col);
    // virtual void takeDamage(Character* enemy);
    virtual bool isDead();
    // virtual void attack(Character* target);
    virtual void beAttackedBy(Character* attacker);
    static int calculateDamage(int atk, int def);

};

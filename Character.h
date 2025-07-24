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
    int maxHP;

public:
    Character(int hp, int atk, int def, int row, int col, int maxHP);
    virtual ~Character() = default;
    
    virtual int getAtk() const;
    virtual int getDef() const;
    virtual int getHP() const; 
    
    virtual char getSymbol() const = 0;
    virtual bool isPlayer() const;
    virtual int getMaxHP() const;
    virtual void setHP(int newHp) = 0;
    virtual void setPosition(int r, int c);
    virtual std::pair<int, int> getPosition() const;

    virtual void move(int row, int col);
    // virtual void takeDamage(Character* enemy);
    virtual bool isDead();
    // virtual void attack(Character* target);
    virtual void beAttackedBy(Character* attacker);
    static int calculateDamage(int atk, int def);

};

// export module Character;

// import Player;
// import Enemy;
// import Item;

// export
#pragma once
#include "Item.h"
#include <utility>
#include <memory>
#include <algorithm>

class Character {    
protected:
    int hp, atk, def;
    int row = -1, col = -1;
    int maxHP = 1;

public:
    Character(int hp, int atk, int def, int row, int col, int maxHP = 1);
    virtual ~Character() = default;
    
    virtual int getAtk() const;
    virtual int getDef() const;
    virtual int getHP() const; 
    virtual std::string getRace() const = 0;
    virtual char getSymbol() const = 0;
    virtual bool isPlayer() const;
    virtual int getMaxHP() const;
    void setHP(int newHp);
    virtual void setPosition(int r, int c);
    virtual std::pair<int, int> getPosition() const;

    virtual void move(int row, int col);
    virtual void takeDamage(int damage);
    virtual bool isDead();
    virtual int beAttackedBy(Character* attacker);
    static int calculateDamage(int atk, int def);

};

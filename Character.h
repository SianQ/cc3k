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
    int x = -1, y = -1;
    int maxHP = 1;

public:
    Character(int hp, int atk, int def, int x, int y, int maxHP = 1);
    Character();
    virtual ~Character();
    
    virtual int getAtk() const;
    virtual int getDef() const;
    virtual int getHP() const; 
    virtual std::string getRace() const;
    virtual char getSymbol() const;
    virtual bool isPlayer() const;
    virtual int getMaxHP() const;
    void setHP(int newHp);
    virtual void setPosition(int r, int c);
    virtual std::pair<int, int> getPosition() const;

    virtual bool isDead();
    virtual int beAttackedBy(Character* attacker);
    static int calculateDamage(int atk, int def);

};

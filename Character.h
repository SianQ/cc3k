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

class Character
{
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
    // virtual void attack(Character* target);

    // Accessors
    int getHP() const;
    int getAtk() const;
    int getDef() const;
    std::pair<int, int> getPosition() const;

    // Returns true if HP ≤ 0
    bool isDead();

    // Called when this character is attacked by another
    virtual void beAttackedBy(Character *attacker);

    // Take damage directly
    virtual void takeDamage(int damage);

    // Damage formula: ceil((100/(100 + def)) * atk)
    static int calculateDamage(int atk, int def);

    // Override in Player to return true
    virtual bool isPlayer() const { return false; }

    // Override in Player to return race name
    virtual std::string getRace() const { return ""; }
};

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

class CharacterDecorator : public Character {
    protected:
        std::shared_ptr<Character> base;
    
    public:
        CharacterDecorator(std::shared_ptr<Character> base) : Character(base->getHP(), base->getAtk(), base->getDef(), base->getPosition().first, base->getPosition().second), base{base} {}
        virtual ~CharacterDecorator() = default;
    
        // By default, just forward calls to the base
        int getAtk() const override { return base->getAtk(); }
        int getDef() const override { return base->getDef(); }
        int getHP() const override { return base->getHP(); }
        // void attack(Character* target) override { base->attack(target); }

        virtual isPlayer() = 0;
};

class BoostAtkDecorator : public CharacterDecorator {
    int boost;

public:
    BoostAtkDecorator(std::shared_ptr<Character> base, int amount)
        : CharacterDecorator(base), boost{amount} {}

    int getAtk() const override {
        return base->getAtk() + boost;
    }
};

class WoundDefDecorator : public CharacterDecorator {
    int penalty;

public:
    WoundDefDecorator(std::shared_ptr<Character> base, int amount)
        : CharacterDecorator(base), penalty{amount} {}

    int getDef() const override {
        return std::max(0, base->getDef() - penalty);
    }
};

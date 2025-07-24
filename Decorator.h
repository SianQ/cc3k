#include "Character.h"
#include <memory>
#include <algorithm>

class CharacterDecorator : public Character {
protected:
    std::shared_ptr<Character> base;

public:
    CharacterDecorator(std::shared_ptr<Character> base);
    virtual ~CharacterDecorator() = default;

    int getAtk() const override;
    int getDef() const override;
    int getHP() const override;

};

class BoostAtkDecorator : public CharacterDecorator {
    int boost;
public:
    BoostAtkDecorator(std::shared_ptr<Character> base, int amount);
    int getAtk() const override {
        return base->getAtk() + boost;
    }
};

class WoundAtkDecorator : public CharacterDecorator {
    int penalty;
public:
    WoundAtkDecorator(std::shared_ptr<Character> base, int amount);
    int getAtk() const override {
        return std::max(0, base->getAtk() - penalty);
    }
};

class BoostDefDecorator : public CharacterDecorator {
    int boost;
public:
    BoostDefDecorator(std::shared_ptr<Character> base, int amount);
    int getDef() const override {
        return base->getDef() + boost;
    }
};

class WoundDefDecorator : public CharacterDecorator {
    int penalty;
public:
    WoundDefDecorator(std::shared_ptr<Character> base, int amount);
        int getDef() const override;
};

std::shared_ptr<Character> unwrap(std::shared_ptr<Character> decorated);

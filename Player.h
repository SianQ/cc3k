// export module Player;

// export
#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
class Potion;
class Gold;
#include <memory>
#include <string>
#include <vector>

class Player: public Character {
protected:
    int gold = 0;

public:
    inline static const std::vector<std::string> RaceNames = {
        "Shade",
        "Vampire",
        "Troll",
        "Goblin",
        "Drow"
    };

    static std::unique_ptr<Player> create(const std::string& race);
    virtual ~Player() = default;

    virtual void usePotion(class Potion* potion) = 0;
    virtual void pickUpGold(class Gold* gold) = 0;
    virtual void resetFloorEffects();
    virtual void attack(Character* target);
    virtual void beAttackedBy(Character* enemy);
    virtual void pickUp(Item* item);
    virtual void useItem(Item* item);

    friend class Level; // Allow Level to access private members
    friend class Enemy; // Allow Enemy to access private members
};
#endif

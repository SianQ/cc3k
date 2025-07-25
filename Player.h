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
    std::string race;

public:
    inline static const std::vector<std::string> RaceNames = {
        "Shade",
        "Vampire",
        "Troll",
        "Goblin",
        "Drow"
    };

    static std::unique_ptr<Player> create(const std::string& race);
    Player(int hp, int atk, int def, int maxHP, const std::string& race);
    virtual ~Player();

    void usePotion(class Potion* potion);
    void pickUpGold(class Gold* gold);
    virtual void resetFloorEffects();
    virtual void attack(Character* target);
    virtual int beAttackedBy(Character* enemy) override;
    virtual void pickUp(Item* item);
    virtual void useItem(Item* item);
    virtual bool isPlayer() const override;
    virtual std::string getRace() const override;
    virtual int getGoldNum() const;
    virtual char getSymbol() const override;

    friend class Level; // Allow Level to access private members
    friend class Enemy; // Allow Enemy to access private members
};
#endif

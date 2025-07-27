export module Player;

import Character;
import Gold;
import Potion;
import <memory>;
import <string>;
import <vector>;

export class Player: public Character {
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


    Player(int hp, int atk, int def, int maxHP, const std::string& race);
    Player();
    virtual ~Player();

    void usePotion(Potion* potion);
    void pickUpGold(Gold* gold);
    virtual void attack(Character* target);
    virtual int beAttackedBy(Character* enemy) override;
    virtual bool isPlayer() const override;
    virtual std::string getRace() const override;
    virtual int getGoldNum() const;
    virtual char getSymbol() const override;

};

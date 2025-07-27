export module Player;

import Character;
import Race;

import <memory>;
import <string>;
import <vector>;

export class Player: public Character {
protected:
    int gold = 0;

public:
    Player(Race race, int hp, int atk, int def);
    virtual ~Player();

    virtual bool isPlayer() const override;
    int getGoldNum() const;
    void addGoldNum(int newGold);

    virtual int attack(Character* target, bool isSuccess);
    void takeDamage(int damage, const Character* source);
    
    virtual void perTermEvent();
};

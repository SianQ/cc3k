export module Player;

import Character;

import <memory>;
import <string>;
import <vector>;

export class Player: public Character {
protected:
    int gold = 0;

public:
    Player::Player(Race race, int hp, int atk, int def);
    static std::unique_ptr<Player> create(const std::string& race);
    virtual ~Player();

    virtual bool isPlayer() const override;
    int getGoldNum() const;
    void addGoldNum(int newGold);

    virtual int attack(const Character* target, bool isSuccess) override;
    virtual int takeDamage(const Character* source) override;
    
    virtual void perTermEvent();
};

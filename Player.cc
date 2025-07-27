export module Player;

import Character;
import Gold;

import <memory>;
import <string>;
import <vector>;

export class Player: public Character {
protected:
    int gold = 0;

public:
    static std::unique_ptr<Player> create(const std::string& race);
    PlayerPlayer(Race race, int hp, int atk, int def, int maxHP, const std::string& race);
    virtual ~Player();

    void usePotion(Potion* potion);
    virtual bool isPlayer() const override;
    virtual std::string getRace() const override;
    virtual int getGoldNum() const;
    virtual char getSymbol() const override;

    friend class Level; // Allow Level to access private members
    friend class Enemy; // Allow Enemy to access private members
};

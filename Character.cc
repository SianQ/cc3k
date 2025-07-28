export module Character;

import Race;
import <utility>;
import <memory>;
import <algorithm>;

export class Character {    
protected:
    Race race;
    int hp, atk, def;
    int x, y;
    int maxHP;
    char symbol;

public:
    Character(Race race, int hp, int atk, int def);
    ~Character() = default;
    
    virtual int getAtk() const;
    virtual int getDef() const;
    virtual int getHp() const; 
    virtual Race getRace() const;
    virtual char getSymbol() const;
    virtual int getMaxHp() const;
    virtual int getX() const;
    virtual int getY() const;

    virtual void setHp(const int newHp);
    virtual int setMaxHp(int maxHp);
    virtual void setX(const int x);
    virtual void setY(const int y);

    virtual bool isPlayer() const;
    virtual bool isDead() const;

    virtual int attack(Character* target, bool isSuccess) = 0;
    virtual void takeDamage(int damage, const Character* source) = 0;


    virtual int calculateDamage(const int atk, const int def);
};

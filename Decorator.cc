export module Decorator;

import Player;
import Race;
import <memory>;

export class Decorator : public Player {
protected:
    std::shared_ptr<Player> next;

public:
    Decorator(std::shared_ptr<Player> next);

    virtual int    getAtk()       const override;
    virtual int    getDef()       const override;
    virtual int    getHp()        const override;
    virtual Race   getRace()      const override;
    virtual char   getSymbol()    const override;
    virtual int    getMaxHp()     const override;
    virtual int    getX()         const override;
    virtual int    getY()         const override;

    virtual void   setHp(int newHp)          override;
    virtual int    setMaxHp(int newMaxHp)    override;
    virtual void   setX(int newX)            override;
    virtual void   setY(int newY)            override;

    virtual bool   isPlayer()    const override;
    virtual bool   isDead()      const override;

    virtual int    attack(Character* target, bool isSuccess) override;
    virtual void   takeDamage(int damage, const Character* source) override;

    virtual void   perTermEvent() override;

    virtual int    calculateDamage(int atk, int def) override;
};

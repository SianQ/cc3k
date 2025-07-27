export module Item;

import <string>;

export class Item {
public:
    virtual bool isGold();
    virtual bool isPotion();
    virtual bool isStair();

    virtual char getSymbol() const = 0;
};

export module Stair;

import Item;

export class Stair : public Item {
public:
    ~Stair() override = default;

    bool isGold() override {
        return false;
    }

    bool isPotion() override {
        return false;
    }

    bool isStair() override {
        return true;
    }

    char getSymbol() const override {
        return '\\';  // Display character for stairs
    }
};

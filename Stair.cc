export module Stair;

import Item;

export class Stair : public Item {
public:
    bool isStair() override {
        return true;
    }

    char getSymbol() const override {
        return '\\';  // Display character for stairs
    }
};

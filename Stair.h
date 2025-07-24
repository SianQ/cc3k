#pragma once

#include "Item.h"

/**
 * Represents a staircase to the next floor.
 * Has no effect when used.
 */
class Stair : public Item {
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

    void use(Character &consumer) override {
        // Stairs cannot be "used" in the traditional sense.
        // The game logic (e.g., in Level) should handle stair stepping.
    }

    char getSymbol() const override {
        return '\\';  // Display character for stairs
    }
};

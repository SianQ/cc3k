// Item.h
#pragma once

#include <string>

// Forward declaration
class Character;

/**
 * Abstract base class: common interface for all items (gold, potions, etc.)
 */
class Item {
public:
    virtual ~Item() = default;

    virtual bool isGold() = 0;
    virtual bool isPotion() = 0;
    virtual bool isStair() = 0;

    // Called when a character uses this item
    virtual void use(Character &consumer) = 0;

    // Returns the item name for display
    virtual std::string getName() const = 0;
};

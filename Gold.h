// Gold.h
#pragma once

#include <string>
#include "Item.h"

// Forward declaration
class Character;

/**
 * Gold: when picked up, gives currency to the consumer.
 * If guardedByDragon == true, it cannot be picked up.
 */
class Gold : public Item {
public:
    Gold(int value, bool guarded);

    // If not guarded, adds value to the consumer's gold
    void use(Character &consumer) override;

    // Returns "Gold" or a formatted display name
    std::string getName() const override;

    // Amount of gold to add
    int  getValue() const;

    // Whether this gold is guarded by a dragon
    bool isGuarded() const;

private:
    int  value;
    bool guardedByDragon;
};

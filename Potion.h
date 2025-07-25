// Potion.h
#pragma once

#include <string>
#include "Item.h"
#include "PotionType.h"

// Forward declaration
class Character;

/**
 * Potion: applying use() applies an effect to the consumer
 * and marks the potion as discovered.
 */
class Potion : public Item
{
public:
    Potion(PotionType t);

    // Apply the potion effect to the consumer and mark discovered = true
    void use(Character &consumer) override;

    // If discovered, returns the specific name (e.g. "Restore Health Potion"),
    // otherwise returns "Unknown Potion"
    char getSymbol() const override;

    virtual PotionType getType() const;

    // Override pure virtual functions from Item
    bool isGold() override { return false; }
    bool isPotion() override { return true; }
    bool isStair() override { return false; }

private:
    PotionType type;
    // bool discovered = false;
};

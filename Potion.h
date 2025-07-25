// Potion.h
#pragma once

#include <memory>
#include <string>
#include "Item.h"

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

    // If discovered, returns the specific name (e.g. "Restore Health Potion"),
    // otherwise returns "Unknown Potion"
    
    std::unique_ptr<Potion> create(const PotionType type);

    char getSymbol() const override;
    virtual void use(Character &consumer) override;
    virtual PotionType getType() const override;

    // Override pure virtual functions from Item
    bool isGold() override { return false; }
    bool isPotion() override { return true; }
    bool isStair() override { return false; }

private:
    PotionType type;
    std::string name;
    // bool discovered = false;
};

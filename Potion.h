export module Potion;

// import <memory>;
// import <string>;
// import Item;

// export
// Potion.h


import <memory>;
import <string>;
import Item;
import Character;

/**
 * Potion: applying use() applies an effect to the consumer
 * and marks the potion as discovered.
 */
export class Potion : public Item
{
public:
    Potion(PotionType t);

    // If discovered, returns the specific name (e.g. "Restore Health Potion"),
    // otherwise returns "Unknown Potion"
    
    char getSymbol() const override;
    PotionType getType() const override;

    // Override pure virtual functions from Item
    bool isGold() override { return false; }
    bool isPotion() override { return true; }
    bool isStair() override { return false; }

private:
    PotionType type;
    std::string name;
    // bool discovered = false;
};

export module Potion;

import Item;
import PotionType;
import <string>;

/**
 * Potion: can be consumed by the player.
 * Each potion has a specific type and effect.
 */
export class Potion : public Item {
private:
    PotionType type;

public:
    // Constructor
    Potion(PotionType t);

    // Item interface
    bool isGold() override;
    bool isPotion() override;
    bool isStair() override;
    char getSymbol() const override;
    PotionType getType() const override;

};

export module Item;

// import <string>;
// import PotionType;

// export
// Item.h

import <string>;
import PotionType;

/**
 * Abstract base class: common interface for all items (gold, potions, etc.)
 */
export class Item {
public:
    virtual ~Item();

    virtual bool isGold() = 0;
    virtual bool isPotion() = 0;
    virtual bool isStair() = 0;

    // Returns the item name for display
    virtual char getSymbol() const = 0;

    virtual PotionType getType() const;
};

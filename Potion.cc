export module Potion;

import Item;
import PotionType;

export class Potion : public Item {
private:
    PotionType type;

public:
    Potion(PotionType t);

    bool isPotion() override;
    char getSymbol() const override;
    PotionType getType() const;
};

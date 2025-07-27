module Potion;
import Item;

Potion::Potion(PotionType t) : type(t) {}

char Potion::getSymbol() const {
    return 'P'; // always displayed as 'P' on the map
}

PotionType Potion::getType() const {
    return type;
}

Potion::~Potion() = default;

bool Potion::isGold() {
    return false; // Potions are not gold
}
bool Potion::isPotion() {
    return true; // This is a potion
}
bool Potion::isStair() {
    return false; // Potions are not stairs
}

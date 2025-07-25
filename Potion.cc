#include "Potion.h"
#include "Item.h"

Potion::Potion(PotionType t) : type(t) {}

char Potion::getSymbol() const {
    return 'P'; // always displayed as 'P' on the map
}

PotionType Potion::getType() const {
    return type;
}

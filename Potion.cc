// Potion.cc
#include "Potion.h"
#include "Item.h"
#include <iostream>

Potion::Potion(PotionType t) : type(t) {}

char Potion::getSymbol() const {
    return 'P'; // always displayed as 'P' on the map
}

PotionType Potion::getType() const {
    return type;
}


void Potion::use(Character &consumer) {
    std::cerr << "Empty postion" << std::endl;
}

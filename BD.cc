#pragma once
#include "BD.h"

BoostDefDecorator::BoostDefDecorator(std::shared_ptr<Character> base, int amount = 5)
    : CharacterDecorator(base), boost(amount) {
        if (base->getRace() == "D") {
            boost = boost * 1.5;
        }
    }

int BoostDefDecorator::getDef() const {
    return base->getDef() + boost;
}

PotionType BoostDefDecorator::getType() const {
    return PotionType::BD;
}  


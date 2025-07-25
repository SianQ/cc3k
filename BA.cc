#pragma once
#include "BA.h"

BoostAtkDecorator::BoostAtkDecorator(std::shared_ptr<Character> base, int amount = 5)
    : CharacterDecorator(base), boost(amount) {
        if (base->getRace() == "D") {
            boost = boost * 1.5;
        }
    }

int BoostAtkDecorator::getAtk() const {
    return base->getAtk() + boost;
}

PotionType BoostAtkDecorator::getType() const {
    return PotionType::BA;
}  

std::string BoostAtkDecorator::getName() const {
    return "BA";
}

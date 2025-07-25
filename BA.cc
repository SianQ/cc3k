#pragma once
#include "BA.h"
#include "Character.h"

BoostAtkDecorator::BoostAtkDecorator(Character* next, int amount)
    : Decorator(next), boost(amount) {
        if (next->getRace() == "Drow") {
            boost = boost * 1.5;
        }
    }

int BoostAtkDecorator::getAtk() const {
    return next->getAtk() + boost;
}

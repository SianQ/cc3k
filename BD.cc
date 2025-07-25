#pragma once
#include "BD.h"
#include "Character.h"

BoostDefDecorator::BoostDefDecorator(Character* next, int amount)
    : Decorator(next), boost(amount) {
        if (next->getRace() == "Drow") {
            boost = boost * 1.5;
        }
    }

int BoostDefDecorator::getDef() const {
    return next->getDef() + boost;
}

#pragma once
#include "WD.h"
#include "Player.h"

WoundDefDecorator::WoundDefDecorator(std::shared_ptr<Player> next, int amount)
    : Decorator(next), penalty(amount) {
        if (next->getRace() == "Drow") {
            penalty = penalty * 1.5;
        }
    }

int WoundDefDecorator::getDef() const {
    return std::max(0, next->getDef() - penalty);
}

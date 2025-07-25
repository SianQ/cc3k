#include "WA.h"
#include "Character.h"

WoundAtkDecorator::WoundAtkDecorator(Character* next, int amount)
    : Decorator(next), penalty(amount) {
        if (next->getRace() == "Drow") {
            penalty = penalty * 1.5;
        }
    }

int WoundAtkDecorator::getAtk() const {
    return std::max(0, next->getAtk() - penalty);
}

#include "WD.h"
#include "Character.h"

WoundDefDecorator::WoundDefDecorator(Character* next, int amount)
    : Decorator(next), penalty(amount) {
        if (next->getRace() == "Drow") {
            penalty = penalty * 1.5;
        }
    }

int WoundDefDecorator::getDef() const {
    return std::max(0, next->getDef() - penalty);
}

#include "WD.h"

WoundDefDecorator::WoundDefDecorator(std::shared_ptr<Character> base, int amount = 5)
    : CharacterDecorator(base), penalty(amount) {
        if (base->getRace() == "D") {
            penalty = penalty * 1.5;
        }
    }

int WoundDefDecorator::getDef() const {
    return std::max(0, base->getDef() - penalty);
}
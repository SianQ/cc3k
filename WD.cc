#include "WD.h"

WoundDefDecorator::WoundDefDecorator(std::shared_ptr<Character> base, int amount)
    : CharacterDecorator(base), penalty(amount) {}

int WoundDefDecorator::getDef() const {
    return std::max(0, base->getDef() - penalty);
}
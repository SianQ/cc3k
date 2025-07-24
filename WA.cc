#include "WA.h"

WoundAtkDecorator::WoundAtkDecorator(std::shared_ptr<Character> base, int amount)
    : CharacterDecorator(base), penalty(amount) {}

int WoundAtkDecorator::getAtk() const {
    return std::max(0, base->getAtk() - penalty);
}
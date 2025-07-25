#include "BA.h"

BoostAtkDecorator::BoostAtkDecorator(std::shared_ptr<Character> base, int amount)
    : CharacterDecorator(base), boost(amount) {}

int BoostAtkDecorator::getAtk() const {
    return base->getAtk() + boost;
}
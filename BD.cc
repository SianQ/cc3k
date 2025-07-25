#include "BD.h"

BoostDefDecorator::BoostDefDecorator(std::shared_ptr<Character> base, int amount)
    : CharacterDecorator(base), boost(amount) {}

int BoostDefDecorator::getDef() const {
    return base->getDef() + boost;
}
#include "PH.h"
#include <algorithm>

PHDecorator::PHDecorator(Character* base)
    : Decorator(base) {
        int healed = std::min(10, base->getMaxHP() - base->getHP());
        base->setHP(base->getHP() + healed);
}

PHDecorator::~PHDecorator() {
    delete next;
}

int PHDecorator::getHP() const { return next->getHP(); }
bool PHDecorator::isPlayer() const { return next->isPlayer(); }
#include "PH.h"
#include <algorithm>

PHDecorator::PHDecorator(Character* base)
    : Decorator(base) {
        int damaged = std::min(10, base->getHP());
        base->setHP(base->getHP() - damaged);
}

PHDecorator::~PHDecorator() {
    delete next;
}

int PHDecorator::getHP() const { return next->getHP(); }
bool PHDecorator::isPlayer() const { return next->isPlayer(); }
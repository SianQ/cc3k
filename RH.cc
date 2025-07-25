#include "RH.h"
#include <algorithm>

PHDecorator::PHDecorator(std::shared_ptr<Player> next)
    : Decorator(next) {
        int healed = std::min(10, next->getMaxHP() - next->getHP());
        next->setHP(next->getHP() + healed);
}

int PHDecorator::getHP() const { return next->getHP(); }
bool PHDecorator::isPlayer() const { return next->isPlayer(); }
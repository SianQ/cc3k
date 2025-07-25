#include "WA.h"
#include "Player.h"

WoundAtkDecorator::WoundAtkDecorator(std::shared_ptr<Player> next, int amount)
    : Decorator(next), penalty(amount) {
        if (next->getRace() == "Drow") {
            penalty = penalty * 1.5;
        }
    }

int WoundAtkDecorator::getAtk() const {
    return std::max(0, next->getAtk() - penalty);
}

module RH;
import <algorithm>;

RHDecorator::RHDecorator(std::shared_ptr<Player> next)
    : Decorator(next) {
        int healed = std::min(10, next->getMaxHP() - next->getHP());
        next->setHP(next->getHP() + healed);
}

int RHDecorator::getHP() const { return next->getHP(); }
bool RHDecorator::isPlayer() const { return next->isPlayer(); }
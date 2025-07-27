module PH;
import <algorithm>;

PHDecorator::PHDecorator(std::shared_ptr<Player> next)
    : Decorator(next) {
        int damaged = std::min(10, next->getHP());
        next->setHP(next->getHP() - damaged);
}

int PHDecorator::getHP() const { return next->getHP(); }
bool PHDecorator::isPlayer() const { return next->isPlayer(); }
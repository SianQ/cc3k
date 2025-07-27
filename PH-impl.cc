module PH;
import Race;

PH::PH(std::shared_ptr<Player> next)
: Decorator(next) {
    if (next->getRace() == Race::Drow) {
        next->setHP(next->getHP() - 15);
    } else {
        next->setHP(next->getHP() - 10);
    }
}

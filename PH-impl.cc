module PH;
import Race;

PH::PH(std::shared_ptr<Player> next)
: Decorator(next) {
    if (next->getRace() == Race::Drow) {
        next->setHp(next->getHp() - 15);
    } else {
        next->setHp(next->getHp() - 10);
    }
}

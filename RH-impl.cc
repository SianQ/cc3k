module RH;
import Player;
import Race;

RH::RH(std::shared_ptr<Player> next)
: Decorator(next) {
    if (next->getRace() == Race::Drow) {
        next->setHP(next->getHp() + 15);
    } else {
        next->setHP(next->getHp() + 10);
    }
}

module WA;
import Player;
import Race;

WA::WA(std::shared_ptr<Player> next)
: Decorator(next) {}

int WA::getAtk() const {
    int boost = 5;
    if (next->getRace() == Race::Drow) {
        boost = boost * 1.5;
    }
    return next->getAtk() - boost;
}

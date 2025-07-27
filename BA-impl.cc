module BA;
import Player;
import Race;

BA::BA(std::shared_ptr<Player> next)
    : Decorator(next) {}

int BA::getAtk() const {
    int boost = 5;
    if (next->getRace() == Race::Drow) {
        boost = boost * 1.5;
    }
    return next->getAtk() + boost;
}

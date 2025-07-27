module BA;
import Player;

BA::BA(std::shared_ptr<Player> next, int amount)
    : Decorator(next) {}

BA::~BA() = default;

int BA::getAtk() const {
    int boost = 5;
    if (next->getRace() == "Drow") {
        boost = boost * 1.5;
    }
    return next->getAtk() + boost;
}

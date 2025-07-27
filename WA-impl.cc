module WA;
import Player;

WA::WA(std::shared_ptr<Player> next, int amount)
: Decorator(next) {}

WA::~WA() = default;

int WA::getAtk() const {
    int boost = 5;
    if (next->getRace() == "Drow") {
        boost = boost * 1.5;
    }
    return next->getAtk() - boost;
}

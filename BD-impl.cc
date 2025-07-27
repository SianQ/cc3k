module BD;
import Player;

BD::BD(std::shared_ptr<Player> next, int amount)
    : Decorator(next) {
    }

BD::~BD() = default;

int BD::getDef() const {
    int boost = 5;
    if (next->getRace() == "Drow") {
        boost = boost * 1.5;
    }
    return next->getDef() + boost;
}

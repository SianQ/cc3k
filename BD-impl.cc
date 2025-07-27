module BD;
import Player;
import Race;

BD::BD(std::shared_ptr<Player> next)
    : Decorator(next) {
    }

int BD::getDef() const {
    int boost = 5;
    if (next->getRace() == Race::Drow) {
        boost = boost * 1.5;
    }
    return next->getDef() + boost;
}

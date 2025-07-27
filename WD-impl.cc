module WD;
import Player;

WD::WD(std::shared_ptr<Player> next, int amount)
    : Decorator(next) {
    }

WD::~WD() = default;

int WD::getDef() const {
    int boost = 5;
    if (next->getRace() == "Drow") {
        boost = boost * 1.5;
    }
    return next->getDef() - boost;
}

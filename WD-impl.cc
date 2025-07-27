module WD;
import Player;
import Race;

WD::WD(std::shared_ptr<Player> next)
    : Decorator(next) {
    }

int WD::getDef() const {
    int boost = 5;
    if (next->getRace() == Race::Drow) {
        boost = boost * 1.5;
    }
    return next->getDef() - boost;
}

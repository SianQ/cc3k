module BD;
import Player;

BoostDefDecorator::BoostDefDecorator(std::shared_ptr<Player> next, int amount)
    : Decorator(next), boost(amount) {
        if (next->getRace() == "Drow") {
            boost = boost * 1.5;
        }
    }

int BoostDefDecorator::getDef() const {
    return next->getDef() + boost;
}

export module BD;
import Decorator;
import Player;
import Potion;
import Character;
import <memory>;

export class BoostDefDecorator : public Decorator {
    int boost;
public:
    BoostDefDecorator(std::shared_ptr<Player> next, int amount = 5);
    int getDef() const override;
};

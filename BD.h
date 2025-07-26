export module BD;
import Character;
import Decorator;
import Potion;
export class BoostDefDecorator : public Decorator {
    int boost;
public:
    BoostDefDecorator(std::shared_ptr<Player> next, int amount = 5);
    int getDef() const override;
};

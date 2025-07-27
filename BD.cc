export module BD;
import Player;
import Decorator;
export class BD : public Decorator {
public:
    BoostDefDecorator(std::shared_ptr<Player> next);
    int getDef() const override;
};

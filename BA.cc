export module BA;
import Decorator;
import Player;
import Potion;
import Character;
import <memory>;

export class BoostAtkDecorator : public Decorator {
    int boost;
public:
    BoostAtkDecorator(std::shared_ptr<Player> next, int amount = 5);
    int getAtk() const override;
};

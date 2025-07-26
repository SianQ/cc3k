export module RH;
import Decorator;
import Player;
import Potion;
import Character;
import <memory>;

export class RHDecorator : public Decorator {
public:
    RHDecorator(std::shared_ptr<Player> next);
    int getHP() const override;
    bool isPlayer() const override;
};

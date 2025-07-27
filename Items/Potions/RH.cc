export module RH;
import Character;
import Decorator;
import <algorithm>;

export class RHDecorator : public Decorator {
public:
    RHDecorator(std::shared_ptr<Player> next);
    int getHP() const override;
    bool isPlayer() const override;
};

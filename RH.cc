export module RH;
import Player;
import Decorator;

export class RH : public Decorator {
public:
    RH(std::shared_ptr<Player> next);
    int getHP() const override;
    bool isPlayer() const override;
};

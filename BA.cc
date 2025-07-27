export module BA;
import Decorator;
import Player;
import <memory>;

export class BA : public Decorator {
public:
    BA(std::shared_ptr<Player> next);
    int getAtk() const override;
};

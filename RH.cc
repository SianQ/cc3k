export module RH;
import Player;
import Decorator;
import <memory>;

export class RH : public Decorator {
public:
    RH(std::shared_ptr<Player> next);
};

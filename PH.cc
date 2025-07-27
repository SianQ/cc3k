export module PH;
import Player;
import Decorator;
import <memory>;

export class PH : public Decorator {
public:
    PH(std::shared_ptr<Player> next);
};

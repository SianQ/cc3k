export module WA;
import Player;
import Decorator;

export class WA : public Decorator {
    int penalty;
public:
    WA(std::shared_ptr<Player> next);
    int getAtk() const override;
};

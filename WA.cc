// export module WA;

// import Decorator;
// import Player;

// export
export module WA;
import Decorator;
import Player;
import Potion;
import Character;
import <memory>;

export class WoundAtkDecorator : public Decorator {
    int penalty;
public:
    WoundAtkDecorator(std::shared_ptr<Player> next, int amount = 5);
    int getAtk() const override;
};

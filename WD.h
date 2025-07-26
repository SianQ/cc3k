export module WD;

import Player;
import Decorator;

export class WoundDefDecorator : public Decorator {
    int penalty;
public:
    WoundDefDecorator(std::shared_ptr<Player> next, int amount = 5);
    int getDef() const override;
};

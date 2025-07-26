export module WD;

import Decorator;
import Player;
import Potion;
import Character;
import <memory>;

export class WoundDefDecorator : public Decorator {
    int penalty;
public:
    WoundDefDecorator(std::shared_ptr<Player> next, int amount = 5);
    int getDef() const override;
};

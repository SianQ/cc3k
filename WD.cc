export module WD;

import Player;
import Decorator;

export class WD : public Decorator {
public:
    WoundDefDecorator(std::shared_ptr<Player> next);
    int getDef() const override;
};

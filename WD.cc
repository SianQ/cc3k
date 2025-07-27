export module WD;

import Player;
import Decorator;
import <memory>;

export class WD : public Decorator {
public:
    WD(std::shared_ptr<Player> next);
    int getDef() const override;
};

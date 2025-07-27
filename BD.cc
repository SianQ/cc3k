export module BD;
import Player;
import Decorator;
import <memory>;

export class BD : public Decorator {
public:
    BD(std::shared_ptr<Player> next);
    int getDef() const override;
};

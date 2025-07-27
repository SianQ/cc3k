export module Decorator;
import Player;
import <memory>;

export class Decorator: public Player {
protected:
    std::shared_ptr<Player> next;
public:
    Decorator(std::shared_ptr<Player> next);
};

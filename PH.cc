export module PH;
import Player;
import Decorator;

export class PH : public Decorator {
public:
    PHDecorator(std::shared_ptr<Player> next);
};

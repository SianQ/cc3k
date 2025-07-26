export module PH;
import Decorator;
import Player;
import Potion;
import Character;
import <memory>;

export class PHDecorator : public Decorator {
public:
    PHDecorator(std::shared_ptr<Player> next);

    int getHP() const override;
    bool isPlayer() const override;
};

export module PH;
import Character;
import Decorator;
import <algorithm>;

export class PHDecorator : public Decorator {
public:
    PHDecorator(std::shared_ptr<Player> next);

    int getHP() const override;
    bool isPlayer() const override;
};

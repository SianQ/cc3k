#include "Decorator.h"
#include "Player.h"

class WoundAtkDecorator : public Decorator {
    int penalty;
public:
    WoundAtkDecorator(std::shared_ptr<Player> next, int amount = 5);
    int getAtk() const override;
};

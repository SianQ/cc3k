#include "Character.h"
#include "Decorator.h"
#include <algorithm>

class PHDecorator : public Decorator {
public:
    PHDecorator(std::shared_ptr<Player> next);

    int getHP() const override;
    bool isPlayer() const override;
};

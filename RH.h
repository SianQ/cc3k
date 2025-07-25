#include "Character.h"
#include "Decorator.h"
#include <algorithm>

class PHDecorator : public Decorator {
public:
    PHDecorator(Character* base);
    ~PHDecorator();
    int getHP() const override;
    bool isPlayer() const override;
};

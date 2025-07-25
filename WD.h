#include "Character.h"
#include "Decorator.h"
#include "Potion.h"

class WoundDefDecorator : public Decorator {
    int penalty;
public:
    WoundDefDecorator(Character* base, int amount = 5);
    int getDef() const override;
};

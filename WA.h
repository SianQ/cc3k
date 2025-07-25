#include "Character.h"
#include "Decorator.h"
#include "Potion.h"

class WoundAtkDecorator : public Decorator {
    int penalty;
public:
    WoundAtkDecorator(Character* base, int amount = 5);
    int getAtk() const override;
};

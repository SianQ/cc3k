#include "Decorator.h"

class WoundDefDecorator : public CharacterDecorator {
    int penalty;
public:
    WoundDefDecorator(std::shared_ptr<Character> base, int amount);
    int getDef() const override;
};
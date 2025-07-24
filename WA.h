#include "Decorator.h"

class WoundAtkDecorator : public CharacterDecorator {
    int penalty;
public:
    WoundAtkDecorator(std::shared_ptr<Character> base, int amount);
    int getAtk() const override;
};
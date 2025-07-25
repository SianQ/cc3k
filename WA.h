#include "Decorator.h"
#include "Potion.h"

class WoundAtkDecorator : public CharacterDecorator {
    int penalty;
public:
    WoundAtkDecorator(std::shared_ptr<Character> base, int amount);
    int getAtk() const override;
    PotionType getType() const override;
    std::string getName() const override;
};

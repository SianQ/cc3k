#include "WA.h"

WoundAtkDecorator::WoundAtkDecorator(std::shared_ptr<Character> base, int amount = 5)
    : CharacterDecorator(base), penalty(amount) {
        if (base->getRace() == "D") {
            penalty = penalty * 1.5;
        }
    }

int WoundAtkDecorator::getAtk() const {
    return std::max(0, base->getAtk() - penalty);
}

PotionType WoundAtkDecorator::getType() const {
    return PotionType::WA;
}  

std::string WoundAtkDecorator::getName() const {
    return "WA";
} 

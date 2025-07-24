#include "Decorator.h"
#include <memory>

class BoostAtkDecorator : public CharacterDecorator {
    int boost;
public:
    BoostAtkDecorator(std::shared_ptr<Character> base, int amount);
    int getAtk() const override {
        return base->getAtk() + boost;
    }
};
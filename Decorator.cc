#include "Decorator.h"

CharacterDecorator::CharacterDecorator(std::shared_ptr<Character> base)
    : Character(base->getHP(), base->getAtk(), base->getDef(), base->getPosition().first, base->getPosition().second, base->getMaxHP()), base{base} {}

int CharacterDecorator::getAtk() const {
    return base->getAtk();
}

int CharacterDecorator::getDef() const {
    return base->getDef();
}

int CharacterDecorator::getHP() const {
    return base->getHP();
}

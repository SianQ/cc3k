// === Decorator.h ===


\#endif

// === Decorator.cc ===
#include "Decorator.h"

CharacterDecorator::CharacterDecorator(std::shared_ptr<Character> base)
    : Character(base->getHP(), base->getAtk(), base->getDef(), base->getPosition().first, base->getPosition().second), base{base} {}

int CharacterDecorator::getAtk() const {
    return base->getAtk();
}

int CharacterDecorator::getDef() const {
    return base->getDef();
}

int CharacterDecorator::getHP() const {
    return base->getHP();
}

bool CharacterDecorator::isPlayer() {
    return base->isPlayer();
}

BoostAtkDecorator::BoostAtkDecorator(std::shared_ptr<Character> base, int amount)
    : CharacterDecorator(base), boost{amount} {}

int BoostAtkDecorator::getAtk() const {
    return base->getAtk() + boost;
}

WoundAtkDecorator::WoundAtkDecorator(std::shared_ptr<Character> base, int amount)
    : CharacterDecorator(base), penalty{amount} {}

int WoundAtkDecorator::getAtk() const {
    return std::max(0, base->getAtk() - penalty);
}

BoostDefDecorator::BoostDefDecorator(std::shared_ptr<Character> base, int amount)
    : CharacterDecorator(base), boost{amount} {}

int BoostDefDecorator::getDef() const {
    return base->getDef() + boost;
}

WoundDefDecorator::WoundDefDecorator(std::shared\_ptr<Character> base, int amount)
    : CharacterDecorator(base), penalty{amount} {}

int WoundDefDecorator::getDef() const {
    return std::max(0, base->getDef() - penalty);
}

std::shared_ptr<Character> unwrap(std::shared_ptr<Character> decorated) {
    auto ptr = decorated;
    while (auto d = std::dynamic_pointer_cast<CharacterDecorator>(ptr)) {
        ptr = d->base;
    }
    return ptr;
}

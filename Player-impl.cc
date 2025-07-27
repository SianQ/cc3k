module Player;

import Race;
import Shade;
import Drow;
import Vampire;
import Troll;
import Goblin;

Player::Player(Race race, int hp, int atk, int def)
    : Character(race, hp, atk, def) {}

std::unique_ptr<Player> Player::create(const Race race) {
    if (race == Race::Drow) return std::make_unique<Drow>();
    if (race == Race::Vampire) return std::make_unique<Vampire>();
    if (race == Race::Troll) return std::make_unique<Troll>();
    if (race == Race::Goblin) return std::make_unique<Goblin>();
    if (race == Race::Shade) return std::make_unique<Shade>();
    return nullptr;
}

int Player::getGoldNum() const { return gold; }

void Player::addGoldNum(int newGold) {
    gold += newGold;
}

bool Player::isPlayer() const { return true; }

int Player::attack(const Character* target, bool isSuccess) {
    if (target->getRace == Race::Halfling && !isSuccess) { return 0; }
    int damage = Character::calculateDamage(getAtk(), target->getDef());
    target->takeDamage(damage, this);
    return damage;
}

void Player::takeDamage(int damage, const Character* source) {
    hp = std::max(0, hp - damage);
}

void Player::perTermEvent() {
    return;
}

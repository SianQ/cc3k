module Player;

import Race;

Player::Player(Race race, int hp, int atk, int def)
    : Character(race, hp, atk, def) {}

Player::~Player() = default;

int Player::getGoldNum() const { return gold; }

void Player::addGoldNum(int newGold) {
    gold += newGold;
}

bool Player::isPlayer() const { return true; }

int Player::attack(Character* target, bool isSuccess) {
    if (target->getRace ()== Race::Halfling && !isSuccess) { return 0; }
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

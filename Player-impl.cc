module Player;

import Gold;

Player::Player(int hp, int atk, int def, int maxHP, const std::string& race)
    : Character(hp, atk, def, -1, -1, maxHP), race(race) {}

Player::~Player() = default;

std::string Player::getRace() const { return race; }
int Player::getGoldNum() const { return gold; }

char Player::getSymbol() const {
    return '@';
}

void Player::attack(Character* target) {
    target->beAttackedBy(this);
    if (this->getRace() == "Goblin" && target->isDead()) {
        this->gold += 5;
    }
}

int Player::beAttackedBy(Character* enemy) {
    int dmg = Character::calculateDamage(enemy->getAtk(), this->getDef());
    this->hp = std::max(0, this->hp - dmg);
    return dmg;
}

bool Player::isPlayer() const { return true; }

void Player::pickUpGold(Gold* gold) {
    this->gold += gold->getValue();
}

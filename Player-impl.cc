module Player;
import Gold;
import Shade;
import Drow;
import Vampire;
import Troll;
import Goblin;

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

std::unique_ptr<Player> Player::create(const std::string& race) {
    std::string key = race;
    if (key == "Drow") return std::make_unique<Drow>();
    if (key == "Vampire") return std::make_unique<Vampire>();
    if (key == "Troll") return std::make_unique<Troll>();
    if (key == "Goblin") return std::make_unique<Goblin>();
    if (key == "Shade") return std::make_unique<Shade>();
    return nullptr;
}

void Player::pickUpGold(Gold* gold) {
    this->gold += gold->getValue();
}
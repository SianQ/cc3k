module Player;

import Race;
import Gold;
import Shade;
import Drow;
import Vampire;
import Troll;
import Goblin;

Player::Player(Race race, int hp, int atk, int def, int maxHP, const std::string& race)
    : Character(race, hp, atk, def, maxHP) {}
Player::~Player() = default;

int Player::getGoldNum() const { return gold; }

bool Player::isPlayer() const { return true; }

int takeDamage(const Character* source) {
    int damage = Character::calculateDamage(source->getAtk(), def);
    hp = std::max(0, hp - damage);
    return damage;
}

std::unique_ptr<Player> Player::create(const Race race) {
    if (race == Race::Drow) return std::make_unique<Drow>();
    if (race == Race::Vampire) return std::make_unique<Vampire>();
    if (race == Race::Troll) return std::make_unique<Troll>();
    if (race == Race::Goblin) return std::make_unique<Goblin>();
    if (race == Race::Shade) return std::make_unique<Shade>();
    return nullptr;
}

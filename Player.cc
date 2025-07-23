#include "Shade.h"
#include "Drow.h"
#include "Vampire.h"
#include "Troll.h"
#include "Goblin.h"

void Player::attack(Character* target) {
    target->beAttackedBy(this);  // player always hits
}

void Player::beAttackedBy(Character* enemy) {
    int dmg = Character::calculateDamage(enemy->getAtk(), this->getDef());
    this->hp = std::max(0, this->hp - dmg);
}


std::unique_ptr<Player> Player::create(const std::string& race) {
    std::string key = race;
    if (key == "d" || key == "D") return std::make_unique<Drow>();
    if (key == "v" || key == "V") return std::make_unique<Vampire>();
    if (key == "t" || key == "T") return std::make_unique<Troll>();
    if (key == "g" || key == "G") return std::make_unique<Goblin>();
    if (key == "s" || key == "S") return std::make_unique<Shade>();
    return nullptr;
}

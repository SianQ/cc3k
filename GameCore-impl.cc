module GameCore;
import Character;
import Player;
import Map;
import Tile;
import Item;
import Gold;
import Potion;
import Stair;
import Direction;
import PotionType;
import <algorithm>;
import <cmath>;
import <sstream>;
import <random>;
import <utility>;

// ========== Level实现 ==========
Level::Level(const std::string& mapFile, int seed, int floor) 
    : map(mapFile, seed), rng(seed), floorNumber(floor), gameComplete(false) {
    // 从地图文件加载并初始化玩家、敌人等
}

std::pair<int, int> Level::directionToDelta(Direction dir) {
    switch (dir) {
        case Direction::North:     return {-1,  0};
        case Direction::South:     return { 1,  0};
        case Direction::East:      return { 0,  1};
        case Direction::West:      return { 0, -1};
        case Direction::NorthEast: return {-1,  1};
        case Direction::NorthWest: return {-1, -1};
        case Direction::SouthEast: return { 1,  1};
        case Direction::SouthWest: return { 1, -1};
        default:                   return { 0,  0}; 
    }
}

void Level::playerMove(Direction dir) {
    if (!player) return;

    auto [dx, dy] = directionToDelta(dir);
    auto pos = player->getPosition();
    int newX = pos.first + dx;
    int newY = pos.second + dy;

    if (map.inBounds(newX, newY) && map.isPassible(newX, newY)) {
        map.moveCharacter(pos.first, pos.second, newX, newY);
        player->setPosition(newX, newY);

        const Tile& tile = map.getTile(newX, newY);
        if (Item* item = tile.getItem()) {
            if (auto* gold = dynamic_cast<Gold*>(item)) {
                player->pickUpGold(gold);
                map.clearItem(newX, newY);
                appendMessage("PC picks up " + std::to_string(gold->getValue()) + " gold.");
            }
        }
    }
}

void Level::playerAttack(Direction dir) {
    if (!player) return;

    auto [dx, dy] = directionToDelta(dir);
    auto pos = player->getPosition();
    int targetX = pos.first + dx;
    int targetY = pos.second + dy;

    if (map.inBounds(targetX, targetY)) {
        const Tile& tile = map.getTile(targetX, targetY);
        if (Character* enemy = tile.getCharacter()) {
            if (!enemy->isPlayer()) {
                player->attack(enemy);
                if (enemy->isDead()) {
                    appendMessage("PC slays " + enemy->getRace() + ".");
                }
            }
        }
    }
}

void Level::playerPotion(Direction dir) {
    // int x, y;
    // get_xy(dir, x, y);
    // Tile potion_tile = map.getTile(player->getPosition().first + x, player->getPosition().second + y);
    // Item* item = potion_tile.getItem();
    // if (item->isPotion()) {
    //     auto potion = static_cast<Potion*>(item);
    //     map.clearItem(x, y);
    //     switch (potion->getType()) {
    //         case PotionType::WD:
    //             messageLog = "Player uses WD.";
    //             player = std::make_shared<WoundDefDecorator>(player);
    //             break;
    //         case PotionType::WA:
    //             messageLog = "Player uses WA.";
    //             player = std::make_shared<WoundAtkDecorator>(player);
    //             break;
    //         case PotionType::BD:
    //             messageLog = "Player uses BD.";
    //             player = std::make_shared<BoostDefDecorator>(player);
    //             break;
    //         case PotionType::BA:
    //             player = std::make_shared<BoostAtkDecorator>(player);
    //             messageLog = "Player uses BA.";
    //             break;
    //         case PotionType::PH:
    //             messageLog = "Player uses PH.";
    //             player = std::make_shared<PHDecorator>(player);
    //             break;
    //         case PotionType::RH:
    //             messageLog = "Player uses RH.";
    //             player = std::make_shared<RHDecorator>(player);
    //             break;
    //     }
    // }
}

void Level::updateEnemies() {
    for (auto& enemy : enemies) {
        if (enemy && !enemy->isDead()) {
            enemy->act(map, *player, *this);
        }
    }

    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Enemy>& e) { return e->isDead(); }),
        enemies.end()
    );
}

Direction Level::randomDir() {
    std::uniform_int_distribution<int> dist(0, 7);
    return static_cast<Direction>(dist(rng));
}

bool Level::isAttackSuccess() {
    std::uniform_int_distribution<int> dist(1, 2);
    return dist(rng) == 1;
}

void Level::appendMessage(const std::string& msg) {
    messages.push_back(msg);
}

std::vector<std::string> Level::getMessages() const {
    return messages;
}

void Level::clearMessages() {
    messages.clear();
}

const Map& Level::getMap() const {
    return map;
}

const Player& Level::getPlayer() const {
    return *player;
}

Player& Level::getPlayer() {
    return *player;
}

bool Level::isGameComplete() const {
    return gameComplete;
}

int Level::getFloorNumber() const {
    return floorNumber;
}

void Level::placeGold(int value, Tile& tile) {
    if (!tile.getItem()) {
        auto gold = std::make_unique<Gold>(value, false);
        tile.setItem(gold.release());
    }
}

void Level::placePotion(PotionType type, Tile& tile) {
    if (!tile.getItem()) {
        auto potion = std::make_unique<::Potion>(type);
        tile.setItem(potion.release());
    }
}

void Level::placeStairs(Tile& tile) {
    if (!tile.getItem()) {
        auto stairs = std::make_unique<Stair>();
        tile.setItem(stairs.release());
    }
}

// ========== Enemy Implementation ==========
Enemy::Enemy(int hp_, int atk_, int def_, const std::string& typeSymbol,
             const std::string& raceName, bool hostile_, bool isDragon_, int x, int y)
    : Character(hp_, atk_, def_, x, y, hp_),
      hostile(hostile_), isDragon(isDragon_), type(typeSymbol), race(raceName) {}

bool Enemy::isHostile() const { return hostile; }
void Enemy::setHostile(bool h) { hostile = h; }
char Enemy::getSymbol() const { return type[0]; }
std::string Enemy::getRace() const { return race; }

int Enemy::beAttackedBy(Character* attacker) {
    int dmg = this->calculateDamage(attacker->getAtk(), this->getDef());
    this->hp -= dmg;
    return dmg;
}

void Enemy::attack(Player& pc, bool isAttackSuccessful, Level& level) {
    if (isAttackSuccessful) {
        int damage = pc.beAttackedBy(this);
        if (damage > 0) {
            level.appendMessage(type + " deals " + std::to_string(damage) + " damage to PC.");
        }
    } else {
        level.appendMessage(type + " misses PC.");
    }
}

void Enemy::dropLoot(Level& level, Map& map) const {}

void Enemy::act(Map& map, Player& pc, Level& level) {
    if (this->isDead() && !deathProcessed) {
        map.clearCharacter(x, y);
        dropLoot(level, map);
        deathProcessed = true;
        return;
    }
    if (this->isDead()) return;

    auto pos = pc.getPosition();
    if (std::abs(pos.first - x) + std::abs(pos.second - y) == 1) {
        attack(pc, level.isAttackSuccess(), level);
    }

    for (int tries = 0; tries < 4; ++tries) {
        Direction dir = level.randomDir();
        auto [dr, dc] = level.directionToDelta(dir);
        int nr = x + dr, nc = y + dc;
        if (map.isPassible(nr, nc) && map.inBounds(nr, nc)) {
            map.moveCharacter(x, y, nr, nc);
            x = nr; y = nc;
            break;
        }
    }
}

// ========== Human ==========
Human::Human() : Enemy(140, 20, 20, "H", "Human") {}
void Human::dropLoot(Level& level, Map& map) const {
    level.placeGold(2, map.getTile(x, y));
}

// ========== Merchant ==========
bool Merchant::hostileAll = false;
Merchant::Merchant() : Enemy(30, 70, 5, "M", "Merchant", false, false) {}

void Merchant::attack(Player& pc, bool isAttackSuccessful, Level& level) {
    if (!hostileAll) return;
    Enemy::attack(pc, isAttackSuccessful, level);
}

void Merchant::dropLoot(Level& level, Map& map) const {
    level.placeGold(2, map.getTile(x, y));
}

int Merchant::beAttackedBy(Character* attacker) {
    if (attacker && attacker->isPlayer()) {
        hostileAll = true;
    }
    return Enemy::beAttackedBy(attacker);
}

// ========== Dragon ==========
Dragon::Dragon() : Enemy(150, 20, 20, "D", "Dragon", true, true), hoard(nullptr) {}

void Dragon::act(Map& map, Player& pc, Level& level) {
    if (this->isDead() && !deathProcessed) {
        map.clearCharacter(x, y);
        dropLoot(level, map);
        deathProcessed = true;
        return;
    }
    if (this->isDead()) return;

    auto playerPos = pc.getPosition();
    int px = playerPos.first, py = playerPos.second;
    int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    for (auto& [dx, dy] : directions) {
        int nx = x + dx, ny = y + dy;
        if (map.inBounds(nx, ny) && map.getTile(nx, ny).getCharacter() == &pc) {
            attack(pc, level.isAttackSuccess(), level);
            return;
        }
    }

    for (auto& [dx, dy] : directions) {
        int nx = px + dx, ny = py + dy;
        if (!map.inBounds(nx, ny)) continue;
        Item* item = map.getTile(nx, ny).getItem();
        if (item && item->isGold()) {
            if (static_cast<Gold*>(item)->isGuarded()) {
                attack(pc, level.isAttackSuccess(), level);
                return;
            }
        }
    }
}

int Dragon::beAttackedBy(Character* attacker) {
    int dmg = Enemy::beAttackedBy(attacker);
    if (this->isDead() && hoard) {
        if (Item* item = hoard->getItem()) {
            if (Gold* g = dynamic_cast<Gold*>(item)) g->changeGuarded();
        }
    }
    return dmg;
}

void Dragon::setHoard(Tile* tile) {
    hoard = tile;
}

// ========== Halfling ==========
Halfling::Halfling() : Enemy(100, 15, 20, "L", "Halfling") {}

// ========== Orc ==========
Orc::Orc() : Enemy(180, 30, 25, "O", "Orc") {}

Dwarf::Dwarf()
  : Enemy(100, 20, 30, "W", "Dwarf", true, false) {}

Elf::Elf()
  : Enemy(140, 30, 10, "E", "Elf", true, false) {}

void Elf::attack(Player& pc, bool isAttackSuccessful, Level& level) {
    if (isAttackSuccessful) {
        int damage1 = pc.beAttackedBy(this);
        if (damage1 > 0) {
            level.appendMessage("E deals " + std::to_string(damage1) + " damage to PC.");
        }
        
        if(!pc.isDead() && pc.getRace()!="Drow") {
            int damage2 = pc.beAttackedBy(this);
            if (damage2 > 0) {
                level.appendMessage("E deals " + std::to_string(damage2) + " damage to PC.");
            }
        }
    } else {
        level.appendMessage("E misses PC.");
    }
}

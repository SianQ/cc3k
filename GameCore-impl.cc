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
        
        // 检查是否踩到物品
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

void Level::playerUsePotion(Direction dir) {
    if (!player) return;
    
    auto [dx, dy] = directionToDelta(dir);
    auto pos = player->getPosition();
    int targetX = pos.first + dx;
    int targetY = pos.second + dy;
    
    if (map.inBounds(targetX, targetY)) {
        const Tile& tile = map.getTile(targetX, targetY);
        if (Item* item = tile.getItem()) {
            if (auto* potion = dynamic_cast<::Potion*>(item)) {
                // 使用药水逻辑
                map.clearItem(targetX, targetY);
                appendMessage("PC uses potion.");
            }
        }
    }
}

void Level::updateEnemies() {
    for (auto& enemy : enemies) {
        if (enemy && !enemy->isDead()) {
            enemy->act(map, *player, *this);
        }
    }
    
    // 清理死亡的敌人
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
    return dist(rng) == 1; // 50%几率
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

void Level::placeGold(int value, Tile* tile) {
    if (tile && !tile->getItem()) {
        auto gold = std::make_unique<Gold>(value, false);
        tile->setItem(gold.release());
    }
}

void Level::placePotion(PotionType type, Tile* tile) {
    if (tile && !tile->getItem()) {
        auto potion = std::make_unique<::Potion>(type);
        tile->setItem(potion.release());
    }
}

void Level::placeStairs(Tile* tile) {
    if (tile && !tile->getItem()) {
        auto stairs = std::make_unique<Stair>();
        tile->setItem(stairs.release());
    }
}

// ========== Enemy实现 ==========
Enemy::Enemy(int hp_, int atk_, int def_, const std::string& typeSymbol,
             bool hostile_, bool isDragon_, int x, int y)
    : Character(hp_, atk_, def_, x, y, hp_), 
      hostile(hostile_), isDragon(isDragon_), type(typeSymbol) {}

static inline std::pair<int,int> dirToDelta(Direction d) {
    switch (d) {
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

void Enemy::act(Map& map, Player& pc, Level& level) {
    if (this->isDead()) return;

    // 检查玩家是否相邻
    auto playerPos = pc.getPosition();
    int playerX = playerPos.first;
    int playerY = playerPos.second;
    
    if (std::abs(playerX - x) + std::abs(playerY - y) == 1) {
        attack(pc, level.isAttackSuccess(), level);
    }

    // 随机移动
    for (int tries = 0; tries < 4; ++tries) {
        Direction dir = level.randomDir();
        auto [dr, dc] = dirToDelta(dir);
        int nr = x + dr, nc = y + dc;
        if (map.isPassible(nr, nc) && map.inBounds(nr, nc)) { 
            map.moveCharacter(x, y, nr, nc);
            x = nr;
            y = nc;
            break;
        }
    }
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

int Enemy::beAttackedBy(Character* attacker) {
    int dmg = this->calculateDamage(attacker->getAtk(), this->getDef());
    this->hp -= dmg;
    return dmg;
}

void Enemy::dropLoot(Level& level, Map& map) const {
    // 默认实现 - 什么都不做
}

bool Enemy::isHostile() const { return hostile; }
void Enemy::setHostile(bool h) { hostile = h; }
char Enemy::getSymbol() const { return type[0]; }
std::string Enemy::getRace() const { return type; }

// ========== 具体Enemy子类实现 ==========
Human::Human() : Enemy(140, 20, 20, "Human", false) {}

void Human::dropLoot(Level& level, Map& map) const {
    const Tile& tile = map.getTile(x, y);
    level.placeGold(2, const_cast<Tile*>(&tile));
}

Merchant::Merchant() : Enemy(30, 70, 5, "Merchant", false) {}

void Merchant::dropLoot(Level& level, Map& map) const {
    const Tile& tile = map.getTile(x, y);
    level.placeGold(4, const_cast<Tile*>(&tile));
}

Dragon::Dragon() : Enemy(150, 20, 20, "Dragon", true, true) {}

void Dragon::act(Map& map, Player& pc, Level& level) {
    if (this->isDead()) return;
    
    // 检查玩家是否相邻
    auto playerPos = pc.getPosition();
    int playerX = playerPos.first;
    int playerY = playerPos.second;
    
    if (std::abs(playerX - x) + std::abs(playerY - y) == 1) {
        attack(pc, level.isAttackSuccess(), level);
    }
    
    // Dragons never move (they are stationary)
}

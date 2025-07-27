module GameCore;
import <algorithm>;
import <cmath>;
import <sstream>;
import <random>;

// ========== Level实现 ==========
Level::Level(const std::string& mapFile, int seed, int floor) 
    : map(mapFile, seed), rng(seed), floorNumber(floor), gameComplete(false) {
    // 从地图文件加载并初始化玩家、敌人等
    // TODO: 实现地图解析和对象初始化
}

void Level::playerMove(Direction dir) {
    if (!player) return;
    
    auto [dx, dy] = directionToDelta(dir);
    int newX = player->getX() + dx;
    int newY = player->getY() + dy;
    
    if (map.inBounds(newX, newY) && map.isPassible(newX, newY)) {
        map.moveCharacter(player->getX(), player->getY(), newX, newY);
        player->setPosition(newX, newY);
        
        // 检查是否踩到物品
        Tile* tile = map.getTile(newX, newY);
        if (Item* item = tile->getItem()) {
            // 处理拾取物品逻辑
            if (auto* gold = dynamic_cast<Gold*>(item)) {
                player->pickUpGold(gold);
                tile->setItem(nullptr);
                appendMessage("PC picks up " + std::to_string(gold->getValue()) + " gold.");
            }
        }
    }
}

void Level::playerAttack(Direction dir) {
    if (!player) return;
    
    auto [dx, dy] = directionToDelta(dir);
    int targetX = player->getX() + dx;
    int targetY = player->getY() + dy;
    
    if (map.inBounds(targetX, targetY)) {
        Tile* tile = map.getTile(targetX, targetY);
        if (Character* enemy = tile->getCharacter()) {
            if (!enemy->isPlayer()) {
                player->attack(enemy);
                if (enemy->isDead()) {
                    appendMessage("PC slays " + enemy->getRace() + ".");
                    // 敌人死亡会在下次updateEnemies中处理
                }
            }
        }
    }
}

void Level::playerUsePotion(Direction dir) {
    if (!player) return;
    
    auto [dx, dy] = directionToDelta(dir);
    int targetX = player->getX() + dx;
    int targetY = player->getY() + dy;
    
    if (map.inBounds(targetX, targetY)) {
        Tile* tile = map.getTile(targetX, targetY);
        if (Item* item = tile->getItem()) {
            if (auto* potion = dynamic_cast<Potion*>(item)) {
                // 使用药水逻辑
                // TODO: 实现药水效果应用到玩家
                tile->setItem(nullptr);
                appendMessage("PC uses " + potion->getName() + ".");
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
        auto gold = std::make_unique<Gold>(value);
        tile->setItem(gold.release());
    }
}

void Level::placePotion(PotionType type, Tile* tile) {
    if (tile && !tile->getItem()) {
        auto potion = std::make_unique<Potion>(type);
        tile->setItem(potion.release());
    }
}

void Level::placeStairs(Tile* tile) {
    if (tile && !tile->getItem()) {
        auto stairs = std::make_unique<Stair>();
        tile->setItem(stairs.release());
    }
}

// 辅助函数：方向转换为坐标偏移
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
    if (this->isDead() && !deathProcessed) {
        map.clearCharacter(x, y);
        dropLoot(level, map);
        deathProcessed = true;
        return;
    }
    
    if (this->isDead()) return;

    // 检查是否与玩家相邻
    int playerX = pc.getX();
    int playerY = pc.getY();
    if (std::abs(playerX - x) <= 1 && std::abs(playerY - y) <= 1 && 
        (std::abs(playerX - x) + std::abs(playerY - y)) > 0) {
        if (hostile) {
            attack(pc, level.isAttackSuccess(), level);
        }
        return;
    }

    // 如果是龙，不移动
    if (isDragon) return;

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
    int dmg = calculateDamage(attacker->getAtk(), this->getDef());
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
    level.placeGold(2, map.getTile(x, y));
}

Dwarf::Dwarf() : Enemy(100, 20, 30, "Dwarf") {}

Elf::Elf() : Enemy(140, 30, 10, "Elf") {}

void Elf::attack(Player& pc, bool isAttackSuccessful, Level& level) {
    Enemy::attack(pc, isAttackSuccessful, level);
    if (isAttackSuccessful && pc.getRace() == "Drow") {
        Enemy::attack(pc, true, level); // 对Drow额外攻击
        level.appendMessage("Elf gets an extra attack against Drow!");
    }
}

Orc::Orc() : Enemy(180, 30, 25, "Orc") {}

Halfling::Halfling() : Enemy(100, 15, 20, "Halfling") {}

Goblin::Goblin() : Enemy(70, 5, 10, "Goblin") {}

Troll::Troll() : Enemy(120, 25, 15, "Troll") {}

void Troll::attack(Player& pc, bool isAttackSuccessful, Level& level) {
    Enemy::attack(pc, isAttackSuccessful, level);
    // Troll特殊能力：回血
    if (hp < maxHP) {
        hp = std::min(maxHP, hp + 5);
        level.appendMessage("Troll regenerates health.");
    }
}

Vampire::Vampire() : Enemy(50, 25, 25, "Vampire") {}

void Vampire::attack(Player& pc, bool isAttackSuccessful, Level& level) {
    if (isAttackSuccessful) {
        int damage = pc.beAttackedBy(this);
        if (damage > 0) {
            hp = std::min(maxHP, hp + 5); // 吸血
            level.appendMessage("Vampire deals " + std::to_string(damage) + " damage and gains health.");
        }
    } else {
        level.appendMessage("Vampire misses PC.");
    }
}

Merchant::Merchant() : Enemy(30, 70, 5, "Merchant", false) {}

void Merchant::attack(Player& pc, bool isAttackSuccessful, Level& level) {
    // 商人被攻击后变敌对
    if (!hostile) {
        hostile = true;
        level.appendMessage("Merchant becomes hostile!");
    }
    Enemy::attack(pc, isAttackSuccessful, level);
}

void Merchant::dropLoot(Level& level, Map& map) const {
    level.placeGold(4, map.getTile(x, y));
}

Dragon::Dragon() : Enemy(150, 20, 20, "Dragon", true, true) {}

void Dragon::act(Map& map, Player& pc, Level& level) {
    // Dragon不移动，只在相邻时攻击
    int playerX = pc.getX();
    int playerY = pc.getY();
    if (std::abs(playerX - x) <= 1 && std::abs(playerY - y) <= 1 && 
        (std::abs(playerX - x) + std::abs(playerY - y)) > 0) {
        attack(pc, level.isAttackSuccess(), level);
    }
}

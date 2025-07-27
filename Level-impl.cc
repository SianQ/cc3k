module Level;

import Direction;
import Race;
import PotionType;

import Map;
import Tile;

import Player;
    import Drow;
    import Vampire;
    import Troll;
    import Goblin;
    import Shade;
    
    import BA;
    import BD;
    import RH;
    import PH;
    import WA;
    import WD;

import Enemy;
    import Human;
    import Dwarf;
    import Halfling;
    import Elf;
    import Orc;
    import Merchant;
    import Dragon;

import Item;
    import Stair;
    import Gold;
    import Potion;

import <algorithm>;
import <stdexcept>;
import <random>;
import <utility>;
import <cstdlib>;
import <iostream>;
import <vector>;
import <memory>;
import <string>;

using namespace std;

static constexpr int NON_DRAGON_ENEMIES = 20;
static constexpr int POTION_COUNT       = 10;
static constexpr int GOLD_COUNT         = 10;

Level::Level(const string& mapPath, unsigned seed): 
    map(mapPath, seed),
    rng(seed)
{
    generateEnemies(seed);

    size_t totalSpots = 1       // 1 player            
                      + 1       // 1 staircase
                      + 21      // 21 enemies
                      + 10      // 10 potions
                      + 10;     // 10 gold

    spawnSpots = samplePassableTiles(totalSpots);

    placeNonPlayerObjects();
}

void Level::generateEnemies(unsigned seed) {
    rng.seed(seed);
    uniform_int_distribution<int> roll(1, 18);

    enemyStore.clear();
    enemyStore.reserve(NON_DRAGON_ENEMIES + 1);

    // 20 non‑dragon foes
    for (int i = 0; i < NON_DRAGON_ENEMIES; ++i) {
        int r = roll(rng);
        if      (r <=  4) enemyStore.push_back(make_unique<Human>());
        else if (r <=  7) enemyStore.push_back(make_unique<Dwarf>());
        else if (r <= 12) enemyStore.push_back(make_unique<Halfling>());
        else if (r <= 14) enemyStore.push_back(make_unique<Elf>());
        else if (r <= 16) enemyStore.push_back(make_unique<Orc>());
        else              enemyStore.push_back(make_unique<Merchant>());
    }
    // +1 Dragon
    enemyStore.push_back(make_unique<Dragon>());
}

vector<Tile*> Level::samplePassableTiles(size_t N) {
    vector<Tile*> tiles;
    int W = map.getWidth(), H = map.getHeight();
    tiles.reserve(W * H);

    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            Tile& t = map.getTile(x,y);
            if (t.canSpawn() &&
                t.getCharacter() == nullptr &&
                t.getItem()      == nullptr) {
                tiles.push_back(&t);
            }
        }
    }

    if (N > tiles.size())
        throw runtime_error("Not enough passable tiles");

    shuffle(tiles.begin(), tiles.end(), rng);
    tiles.resize(N);
    return tiles;
}

void Level::placeNonPlayerObjects() {
    size_t idx = 1;  // [0] reserved for PC

    // 1) Staircase
    Tile* t = spawnSpots[idx++];
    auto stair = make_unique<Stair>();
    t->setItem(stair.get());
    itemStore.push_back(move(stair));

    // 2) Enemies
    for (auto& uptr: enemyStore) {
        Tile* t = spawnSpots[idx++];
        t->setCharacter(uptr.get());
        uptr->setX(t->getX());
        uptr->setY(t->getY());

        if (auto dr = dynamic_cast<Dragon*>(uptr.get())) {
            // create a 4‑gold pile, owned by itemStore
            auto g = make_unique<Gold>(4, true);
            Gold* gp = g.get();
            t->setItem(gp);
            itemStore.push_back(move(g));

            // tell the dragon where its hoard lives
            static_cast<Dragon*>(dr)->setHoard(t->getX(), t->getY());        
        }
    }

    // 3) Potions
    uniform_int_distribution<int> potionDist(0,static_cast<int>(PotionType::WD));

    for (int i = 0; i < POTION_COUNT; ++i) {
        Tile* t = spawnSpots[idx++];

        PotionType type = static_cast<PotionType>(potionDist(rng));
        auto p = make_unique<Potion>(type);

        t->setItem(p.get());
        itemStore.push_back(move(p));
    }

    // 4) Gold (Treasure)
    uniform_int_distribution<int> goldDist(1, 2);

    for (int i = 1; i < GOLD_COUNT; ++i) {
        Tile* t = spawnSpots[idx++];

        int amt = goldDist(rng);
        auto g = make_unique<Gold>(amt, false);

        t->setItem(g.get());
        itemStore.push_back(move(g));
    }
}

void Level::appendMessage(const string& message) {
    messageLog += message;
}

bool Level::isAttackSuccess() {
    static bernoulli_distribution coin(0.5);
    return coin(rng);
}

Direction Level::randomDir() {
    int r = static_cast<int>(rng() % 4);
    switch (r) {
      case 0: return Direction::North;
      case 1: return Direction::South;
      case 2: return Direction::East;
      default: return Direction::West;
    }
}

Tile& Level::getDirTile(Character& character, Direction dir) {
    int x = character.getX();
    int y = character.getY();

    switch (dir) { 
        case Direction::North:      y -= 1;           break;
        case Direction::South:      y += 1;           break;
        case Direction::East:       x += 1;           break;
        case Direction::West:       x -= 1;           break;  
        case Direction::NorthEast:  x += 1;  y -= 1;  break;
        case Direction::NorthWest:  x -= 1;  y -= 1;  break;
        case Direction::SouthEast:  x += 1;  y += 1;  break;
        case Direction::SouthWest:  x -= 1;  y += 1;  break;
        default:                                      break;
    }
    if (!map.inBounds(x, y)) {
        std::cerr << "Direction out of bounds: (" + to_string(x) + ", " + to_string(y) + ")";
        throw std::out_of_range("Direction out of bounds");
    }
    Tile& dst = map.getTile(x, y);
    return dst;
}

bool Level::moveCharacter(Character& character, Direction dir) {
    int x = character.getX();
    int y = character.getY();

    int destX = x, destY = y;

    switch (dir) { 
        case Direction::North:      destY = y - 1;                  break;
        case Direction::South:      destY = y + 1;                  break;
        case Direction::East:       destX = x + 1;                  break;
        case Direction::West:       destX = x - 1;                  break;  
        case Direction::NorthEast:  destX = x + 1;  destY = y - 1;  break;
        case Direction::NorthWest:  destX = x - 1;  destY = y - 1;  break;
        case Direction::SouthEast:  destX = x + 1;  destY = y + 1;  break;
        case Direction::SouthWest:  destX = x - 1;  destY = y + 1;  break;
        default:                                                    break;
    }

    Tile& src = map.getTile(x, y);
    Tile& dst = map.getTile(destX, destY);

    if (!map.isPassible(destX, destY)) {
        return false;
    }

    Character* c = src.getCharacter();
    src.setCharacter(nullptr);
    dst.setCharacter(c);
    c->setX(dst.getX());
    c->setY(dst.getY());

    return true;
}

bool Level::moveEnemy(Character& character, Direction dir) {
    int x = character.getX();
    int y = character.getY();

    int destX = x, destY = y;

    switch (dir) { 
        case Direction::North:      destY = y - 1;                  break;
        case Direction::South:      destY = y + 1;                  break;
        case Direction::East:       destX = x + 1;                  break;
        case Direction::West:       destX = x - 1;                  break;  
        case Direction::NorthEast:  destX = x + 1;  destY = y - 1;  break;
        case Direction::NorthWest:  destX = x - 1;  destY = y - 1;  break;
        case Direction::SouthEast:  destX = x + 1;  destY = y + 1;  break;
        case Direction::SouthWest:  destX = x - 1;  destY = y + 1;  break;
        default:                                                    break;
    }

    Tile& src = map.getTile(x, y);
    Tile& dst = map.getTile(destX, destY);

    if (!map.isEnemyPassible(destX, destY)) {
        return false;
    }

    Character* c = src.getCharacter();
    src.setCharacter(nullptr);
    dst.setCharacter(c);
    c->setX(dst.getX());
    c->setY(dst.getY());

    return true;
}

void Level::placeGold(int value, Tile& tile) {
    if (!tile.canSpawn()) {
        throw runtime_error("Cannot place gold on non-spawnable tile");
    }
    if (tile.hasItem()) {
        throw runtime_error("Tile already has an item");
    }
    auto g = make_unique<Gold>(value, false);
    tile.setItem(g.get());
    itemStore.push_back(move(g));
}

void Level::giveRandomGold() {
    uniform_int_distribution<int> goldDist(1, 2);
    int value = goldDist(rng);
    player->addGoldNum(value);
}

void Level::pickUpGold() {
    Tile& tile = map.getTile(player->getX(), player->getY());
    if (!tile.hasItem() || !tile.getItem()->isGold()) {
        messageLog = "Player cannot pick up gold from empty tile.";
        return;
    }
    Gold* gold = static_cast<Gold*>(tile.getItem());
    player->addGoldNum(gold->getValue());
    tile.setItem(nullptr);
    messageLog = "Player picked up " + to_string(gold->getValue()) + " gold.";
}

void Level::playerMove(Direction dir) {
    if (!moveCharacter(*player, dir)) {
        messageLog = "Player cannot move in that direction.";
        return;
    }
    messageLog = "Player moved to (" + to_string(player->getX()) + ", " + to_string(player->getY()) + ").";
    Tile & tile = map.getTile(player->getX(), player->getY());
    if (tile.hasItem()) {
        Item* item = tile.getItem();
        if (item->isGold()) {
            Gold* gold = static_cast<Gold*>(item);
            pickUpGold();
            tile.setItem(nullptr);
            messageLog += " Player picked up " + to_string(gold->getValue()) + " gold.";
        } else if (item->isStair()) {
            levelFinished = true;
                messageLog += " Level completed.";
        }
    }
}

void Level::playerAttack(Direction dir) {

    Tile& tile = getDirTile(*player, dir);
    if (!tile.hasCharacter()) {
        messageLog = "Player attacks empty tile.";
        return;
    }
    int damage = player->attack(tile.getCharacter(), isAttackSuccess());
    if (damage > 0) {
        messageLog = "Player attacks " + toString(tile.getCharacter()->getRace()) + " for " + to_string(damage) + " damage.";
    } else {
        messageLog = "Player attack missed.";
    }
}

void Level::playerPotion(Direction dir) {
    try {
        // getDirTile throws if out of bounds
        Tile &tile = getDirTile(*player, dir);

        if (!tile.hasItem()) {
            messageLog = "Player uses potion on empty tile.";
            return;
        }

        Item* item = tile.getItem();
        if (!item->isPotion()) {
            messageLog = "Player tried to use a non-potion item.";
            return;
        }

        auto potion = static_cast<Potion*>(item);

        // clear the consumed potion
        map.clearItem(tile.getX(), tile.getY());

        // wrap player in the correct decorator
        switch (potion->getType()) {
            case PotionType::WD:
                player = std::make_shared<WD>(player);
                messageLog = "Player uses WD.";
                break;
            case PotionType::WA:
                player = std::make_shared<WA>(player);
                messageLog = "Player uses WA.";
                break;
            case PotionType::BD:
                player = std::make_shared<BD>(player);
                messageLog = "Player uses BD.";
                break;
            case PotionType::BA:
                player = std::make_shared<BA>(player);
                messageLog = "Player uses BA.";
                break;
            case PotionType::PH:
                player = std::make_shared<PH>(player);
                messageLog = "Player uses PH.";
                break;
            case PotionType::RH:
                player = std::make_shared<RH>(player);
                messageLog = "Player uses RH.";
                break;
            default:
                messageLog = "Unknown potion type.";
                break;
        }
    }
    catch (const std::out_of_range&) {
        // cover the "tile out of bounds" case
        messageLog = "Player uses potion out of bounds.";
    }
}

void Level::updateEnemies() {
    for (auto& enemyPtr : enemyStore) {
        Enemy* enemy = enemyPtr.get();

        // 1) Handle dead enemies and drop loot once
        if (enemy->isDead()) {
            if (!enemy->isLooted()) {
                enemy->setLooted(true);
                switch (enemy->getRace()) {
                  case Race::Dragon: {
                    auto dr = static_cast<Dragon*>(enemy);
                    Tile& hoardTile = map.getTile(dr->getHoardX(), dr->getHoardY());
                    if (hoardTile.hasItem() && hoardTile.getItem()->isGold()) {
                        auto gold = static_cast<Gold*>(hoardTile.getItem());
                        gold->setGuarded(false);
                        messageLog += "\nDragon's hoard is now unguarded.";
                    }
                    break;
                  }
                  case Race::Merchant:
                    placeGold(2, map.getTile(enemy->getX(), enemy->getY()));
                    break;
                  case Race::Human:
                    placeGold(1, map.getTile(enemy->getX(), enemy->getY()));
                    break;
                  default:
                    giveRandomGold();
                    messageLog += "\nEnemy defeated, player received gold.";
                    break;
                }
            }
            // dead enemies neither attack nor move
            continue;
        }

        // 2) Attempt to attack if player is adjacent
        bool attacked = false;
        for (Tile* tile : map.getAdjacentTiles(enemy->getX(), enemy->getY())) {
            Character* c = tile->getCharacter();
            if (c && c->isPlayer()) {
                Character* playerPtr = player.get();

                if (enemy->getRace() == Race::Merchant) {
                    auto m = static_cast<Merchant*>(enemy);
                    if (!m->isHostile()) {
                        attacked = true;  // skip movement too
                        break;
                    }
                    int dmg = enemy->attack(playerPtr, isAttackSuccess());
                    if (dmg > 0)
                        appendMessage(toString(enemy->getRace())
                                      + " attacks you for "
                                      + std::to_string(dmg)
                                      + " damage.");
                    else
                        appendMessage(toString(enemy->getRace())
                                      + " attack missed.");
                }
                else if (enemy->getRace() == Race::Elf) {
                    // Elf attacks twice
                    for (int i = 0; i < 2; ++i) {
                        int dmg = enemy->attack(playerPtr, isAttackSuccess());
                        if (dmg > 0)
                            appendMessage(toString(enemy->getRace())
                                          + " attacks you for "
                                          + std::to_string(dmg)
                                          + " damage.");
                        else
                            appendMessage(toString(enemy->getRace())
                                          + " attack missed.");
                    }
                }
                else {
                    // All others attack once
                    int dmg = enemy->attack(playerPtr, isAttackSuccess());
                    if (dmg > 0)
                        appendMessage(toString(enemy->getRace())
                                      + " attacks you for "
                                      + std::to_string(dmg)
                                      + " damage.");
                    else
                        appendMessage(toString(enemy->getRace())
                                      + " attack missed.");
                }

                attacked = true;
                break;  // only one attack per enemy per turn
            }
        }

        // 3) If no attack occurred and this isn't a dragon, move randomly
        if (!attacked && enemy->getRace() != Race::Dragon) {
            Direction dir;
            do {
                dir = randomDir();
            } while (!moveEnemy(*enemy, dir));
        }
    }
}

bool Level::isFinished() {
    Tile tile = map.getTile(player->getX(), player->getY());
    if (tile.getItem() != nullptr && tile.getItem()->isStair()) {
        levelNum++;
        return true;
    }
    else {
        return false;
    }
}

bool Level::isGameOver() {
    if (player->getHp() <= 0) {
        return true;
    }
    return false;
}

bool Level::isGameComplete() {
    if (Level::levelNum >= 5) {
        return true;
    } else {
        return false;
    }
}

std::shared_ptr<Player> Level::create(Race race) {
    switch (race) {
      case Race::Drow:     return std::make_shared<Drow>();
      case Race::Vampire:  return std::make_shared<Vampire>();
      case Race::Troll:    return std::make_shared<Troll>();
      case Race::Goblin:   return std::make_shared<Goblin>();
      case Race::Shade:    return std::make_shared<Shade>();
      default:             return nullptr;
    }
}


void Level::spawnPlayer(const Race race) {
    auto p = create(race);
    if (!p) { return; }
    Tile* t = spawnSpots[0];  // reserved player spot
    t->setCharacter(p.get());
    t->setCharacter(p.get());
    p->setX(t->getX());
    p->setY(t->getY());

    player = move(p);
    messageLog = "Player character has spawned.";
}

const string Level::getMessage() const {
    return messageLog;
}

void Level::clearLog() {
    messageLog = "";
}

void Level::perTermEvent() {
    player->perTermEvent();
}

string Level::getPlayerRace() {
    return toString(player->getRace());
}

int Level::getPlayerHp() const {
    return player->getHp();
}

int Level::getPlayerAtk() const {
    return player->getAtk();
}

int Level::getPlayerDef() const {
    return player->getDef();
}

int Level::getPlayerGold() const {
    return player->getGoldNum();
}

Map& Level::getMap() {
    return map;
}   

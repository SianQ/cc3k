#include <iterator>
module Level;

import Direction;
import EnemyRace;

import Map;

import Tile;

import Player;
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
        uptr->setPosition(t->getX(), t->getY());

        if (auto dr = dynamic_cast<Dragon*>(uptr.get())) {
            // create a 4‑gold pile, owned by itemStore
            auto g = make_unique<Gold>(4, true);
            Gold* gp = g.get();
            t->setItem(gp);
            itemStore.push_back(move(g));

            // tell the dragon where its hoard lives
            static_cast<Dragon*>(dr)->setHoard(t);        
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

Tile& Level::getDirTile(Character& character, Direction dir) const {
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

    Tile& dst = getTile(toX, toY);
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

    Tile& src = getTile(fromX, fromY);
    Tile& dst = getTile(toX, toY);

    if (!map.isPassible(destX, destY)) {
        return false;
    }

    Character* c = src.getCharacter();
    src.setCharacter(nullptr);
    dst.setCharacter(c);
    c->setPosition(dst.getX(), dst.getY());

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

void Level::pickUpGold() {
    Tile& tile = map.getTile(player->getX(), player->getY());
    if (!tile.hasItem() || !tile.getItem()->isGold()) {
        messageLog = "Player cannot pick up gold from empty tile.";
        return;
    }
    Gold* gold = static_cast<Gold*>(tile.getItem());
    player->pickUpGold(gold);
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
            player->pickUpGold(gold);
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
    if (!tile) {
        messageLog = "Player attacks out of bounds.";
        return;
    }
    if (!tile.hasCharacter()) {
        messageLog = "Player attacks empty tile.";
        return;
    }
    int damage = player.attack(getDirTile(*player, dir).getCharacter(), isAttackSuccess());
    if (damage > 0) {
        messageLog = "Player attacks " + getDirTile(*player, dir).getCharacter().getRace() + " for " + to_string(damage) + " damage.";
    } else {
        messageLog = "Player attack missed.";
    }
}

void Level::playerPotion(Direction dir) {
    Tile& tile = getDirTile(*player, dir);
    if (!tile) { 
        messageLog = "Player uses potion out of bounds.";
        return;
    }
    if (!tile.hasItem()) {
        messageLog = "Player uses potion on empty tile.";
        return;
    }
    Item* item = tile.getItem();
    if (item->isPotion()) {
        auto potion = static_cast<Potion*>(item);
        map.clearItem(x, y);
        switch (potion->getType()) {
            case PotionType::WD:
                messageLog = "Player uses WD.";
                player = make_shared<WoundDefDecorator>(player);
                break;
            case PotionType::WA:
                messageLog = "Player uses WA.";
                player = make_shared<WoundAtkDecorator>(player);
                break;
            case PotionType::BD:
                messageLog = "Player uses BD.";
                player = make_shared<BoostDefDecorator>(player);
                break;
            case PotionType::BA:
                player = make_shared<BoostAtkDecorator>(player);
                messageLog = "Player uses BA.";
                break;
            case PotionType::PH:
                messageLog = "Player uses PH.";
                player = make_shared<PHDecorator>(player);
                break;
            case PotionType::RH:
                messageLog = "Player uses RH.";
                player = make_shared<RHDecorator>(player);
                break;
        }
    }
}

void Level::updateEnemies() {
    for (auto& enemy : enemyStore) {
        if (enemy->isDead()) {
            continue;
        }
        if (enemy->isHostile()) {
            for (auto& tile : map.getAdjacentTiles(enemy->getX(), enemy->getY())) {
                if (tile.hasCharacter() && tile.getCharacter().isPlayer()) {
                    enemy->attack(*player, isAttackSuccess());
                    break;
                }
            }
        } else {
            if (enemy->isDragon()) {
                continue;
            }
            while(!moveCharacter(*enemy, randomDir())) {
                Direction dir = randomDir();
            }
        }
    }
}

bool Level::isFinished() const {
    Tile tile = map.getTile(player->getPosition().first, player->getPosition().second);
    if (tile.getItem() != nullptr && tile.getItem()->isStair()) {
        levelNum++;
        return true;
    }
    else {
        return false;
    }
}

bool Level::isGameOver() const {
    if (player->getHP() <= 0) {
        return true;
    }
    return false;
}

bool Level::isGameComplete() const {
    if (Level::levelNum >= 5) {
        return true;
    } else {
        return false;
    }
}

void Level::spawnPlayer(const string& race) {
    auto p = Player::create(race);
    if (!p) { return; }
    Tile* t = spawnSpots[0];  // reserved player spot
    t->setCharacter(p.get());
    t->setCharacter(p.get());
    p->setPosition(t->getX(), t->getY());

    player = move(p);
    messageLog = "Player character has spawned.";
    return true;
}

const string Level::getMessage() const {
    return messageLog;
}

void Level::clearLog() {
    messageLog = "";
}

void Level::perTermEvent() {
    player.perTermEvent();
}

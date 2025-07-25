// Level.cpp
#pragma once
#include "Level.h"         
#include "Stair.h"     
#include "Gold.h"          
#include "Potion.h"
#include "Dragon.h"    
#include "Human.h"
#include "Dwarf.h"
#include "Halfling.h"
#include "Elf.h"
#include "Orc.h"
#include "Merchant.h"
#include "Player.h"
#include "Tile.h"
#include "Map.h"
#include "Character.h"
#include "Enemy.h"
#include "BA.h"
#include "BD.h"
#include "RH.h"
#include "PH.h"
#include "WA.h"
#include "WD.h"


#include <algorithm>       
#include <stdexcept>       
#include <random>          
#include <utility>         
#include <cstdlib>     

static constexpr int NON_DRAGON_ENEMIES = 20;
static constexpr int POTION_COUNT       = 10;
static constexpr int GOLD_COUNT         = 10;

Level::Level(const std::string& mapPath, unsigned seed): 
    map(mapPath, seed),
    rng(seed)
{
    // 1) Build 20 weighted foes + 1 Dragon
    generateEnemies(seed);

    // 2) Reserve spots for PC + stair + enemies + potions + gold
    size_t totalSpots = 1                      // PC
                      + 1                      // staircase
                      + 21    // 21 enemies
                      + 10
                      + 10;
    spawnSpots = samplePassableTiles(totalSpots);

    // 3) Place everything except the PC
    placeNonPlayerObjects();
}

void Level::generateEnemies(unsigned seed) {
    rng.seed(seed);
    std::uniform_int_distribution<int> roll(1, 18);

    enemyStore.clear();
    enemyStore.reserve(NON_DRAGON_ENEMIES + 1);

    // 20 non‑dragon foes
    for (int i = 0; i < NON_DRAGON_ENEMIES; ++i) {
        int r = roll(rng);
        if      (r <=  4) enemyStore.push_back(std::make_unique<Human>());
        else if (r <=  7) enemyStore.push_back(std::make_unique<Dwarf>());
        else if (r <= 12) enemyStore.push_back(std::make_unique<Halfling>());
        else if (r <= 14) enemyStore.push_back(std::make_unique<Elf>());
        else if (r <= 16) enemyStore.push_back(std::make_unique<Orc>());
        else              enemyStore.push_back(std::make_unique<Merchant>());
    }
    // +1 Dragon
    enemyStore.push_back(std::make_unique<Dragon>());
}

std::vector<Tile*> Level::samplePassableTiles(size_t N) {
    std::vector<Tile*> tiles;
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
        throw std::runtime_error("Not enough passable tiles");

    std::shuffle(tiles.begin(), tiles.end(), rng);
    tiles.resize(N);
    return tiles;
}

void Level::placeNonPlayerObjects() {
    size_t idx = 1;  // [0] reserved for PC

    // 1) Staircase
    {
        Tile* t = spawnSpots[idx++];
        auto stair = std::make_unique<Stair>();
        t->setItem(stair.get());
        itemStore.push_back(std::move(stair));
    }

    // 2) Enemies
    for (auto& uptr : enemyStore) {
        Tile* t = spawnSpots[idx++];
        t->setCharacter(uptr.get());
        uptr->setPosition(t->getX(), t->getY());

        if (auto dr = dynamic_cast<Dragon*>(uptr.get())) {
            // create a 4‑gold pile, owned by itemStore
            auto g = std::make_unique<Gold>(4, true);
            Gold* gp = g.get();
            t->setItem(gp);
            itemStore.push_back(std::move(g));

            // tell the dragon where its hoard lives
            static_cast<Dragon*>(dr)->setHoard(t);        }
    }

    // 3) Potions
    std::uniform_int_distribution<int> potionDist(0,static_cast<int>(PotionType::WD));

    for (int i = 0; i < POTION_COUNT; ++i) {
        Tile* t = spawnSpots[idx++];

        // pick a random PotionType
        PotionType type = static_cast<PotionType>(potionDist(rng));
        auto p = std::make_unique<Potion>(type);

        t->setItem(p.get());
        itemStore.push_back(std::move(p));
    }

    // 4) Gold (Treasure)
    std::uniform_int_distribution<int> goldDist(1, 2);

    for (int i = 1; i < GOLD_COUNT; ++i) {
        Tile* t = spawnSpots[idx++];

        int amt = goldDist(rng);
        auto g = std::make_unique<Gold>(amt, false);

        t->setItem(g.get());
        itemStore.push_back(std::move(g));
    }
}

bool Level::spawnPlayer(const std::string& race) {
    auto p = Player::create(race);
    if (!p) return false;

    Tile* t = spawnSpots[0];  // reserved player spot
    t->setCharacter(p.get());
    t->setCharacter(p.get());
    p->setPosition(t->getX(), t->getY());

    player = std::move(p);
    messageLog = "Player character has spawned.";
    return true;
}

const Player& Level::getPlayer() const {
    return *player;
}

const Map& Level::getMap() const {
    return map;
}

const std::string Level::getMessage() const {
    return messageLog;
}

void Level::clearLog() {
    messageLog = "";
}

void Level::appendMessage(const std::string& message) {
    messageLog += message;
}

void get_xy(Direction dir, int& x, int& y) {
    switch (dir) {
        case Direction::North:
            x = 0;
            y = -1;
            break;
        case Direction::South:
            x = 0;
            y = 1;
            break;
        case Direction::East:
            x = 1;
            y = 0;
            break;
        case Direction::West:
            x = -1;
            y = 0;
            break;  
        case Direction::NorthEast:
            x = 1;
            y = 1;
            break;
        case Direction::NorthWest:
            x = -1; 
            y = 1;
            break;
        case Direction::SouthEast:
            x = 1;
            y = -1;
            break;
        case Direction::SouthWest:
            x = -1;
            y = -1;
            break;
        default:
            break;
    }
}

void Level::playerMove(Direction dir) {
    int x, y;
    get_xy(dir, x, y);
    int destX = player->getPosition().first + x;
    int destY = player->getPosition().second + y;
    if (map.isPassible(destX, destY)) {
        map.moveCharacter(player->getPosition().first, player->getPosition().second, player->getPosition().first + x, player->getPosition().second + y);
        if (player->getRace() == "Troll" && player->getHP() < player->getMaxHP()) {
            player->setHP(player->getHP() + 5);
        }
    }
    else if (map.getTile(destX, destY).getItem() != nullptr) {
        Item* item = map.getTile(destX, destY).getItem();
        if (item->isGold()) {
            Gold* gold = static_cast<Gold*>(item);
            player->pickUpGold(gold);
            map.clearTile(destX, destY);
            messageLog = "Player picks up " + std::to_string(gold->getValue()) + " gold.";
        }
    }
    else {
        messageLog = "Player cannot move to " + std::to_string(destX) + ", " + std::to_string(destY) + ".";
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

void Level::playerAttack(Direction dir) {
    int x, y;
    int damage = 0;
    get_xy(dir, x, y);
    Tile& character_tile = map.getTile(player->getPosition().first + x, player->getPosition().second + y);
    Character* enemy = character_tile.getCharacter();
    if (enemy != nullptr) {
        bool attackSuccess = Level::isAttackSuccess();
        if (enemy->getRace() == "L" && attackSuccess && player->getRace() != "Vampire") {
            player->setHP(player->getHP() + 5);
        }
        else if (!attackSuccess) {
            messageLog = messageLog + "Player attacks " + enemy->getSymbol() + " but misses.\n";
        }
        else { damage = enemy->beAttackedBy(player.get()); }
    }
    messageLog = "Player deals " + std::to_string(damage) + " damage to " + enemy->getSymbol() + " ( " + std::to_string(enemy->getHP()) + " HP ).\n";
}

void Level::playerPotion(Direction dir) {
    int x, y;
    get_xy(dir, x, y);
    Tile potion_tile = map.getTile(player->getPosition().first + x, player->getPosition().second + y);
    Item* item = potion_tile.getItem();
    if (item->isPotion()) {
        auto potion = static_cast<Potion*>(item);
        map.clearTile(x, y);
        switch (potion->getType()) {
            case PotionType::WD:
                messageLog = "Player uses WD.";
                player = std::make_shared<WoundDefDecorator>(player);
                break;
            case PotionType::WA:
                messageLog = "Player uses WA.";
                player = std::make_shared<WoundAtkDecorator>(player);
                break;
            case PotionType::BD:
                messageLog = "Player uses BD.";
                player = std::make_shared<BoostDefDecorator>(player);
                break;
            case PotionType::BA:
                player = std::make_shared<BoostAtkDecorator>(player);
                messageLog = "Player uses BA.";
                break;
            case PotionType::PH:
                messageLog = "Player uses PH.";
                player = std::make_shared<PHDecorator>(player);
                break;
            case PotionType::RH:
                messageLog = "Player uses RH.";
                player = std::make_shared<RHDecorator>(player);
                break;
        }
    }
}

void Level::placeGold(int value, Tile& tile) {
    auto g = std::make_unique<Gold>(value, false);
    tile.setItem(g.get());
    itemStore.push_back(std::move(g));
}

bool Level::isGameOver() const {
    if (levelNum == 5 || player->getHP() <= 0) {
        return true;
    }
    return false;
}

bool Level::isAttackSuccess() {
    static std::bernoulli_distribution coin(0.5);
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

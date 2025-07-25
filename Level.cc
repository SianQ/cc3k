#include "Level.h"
#include "Human.h"
#include "Dwarf.h"
#include "Halfling.h"
#include "Elf.h"
#include "Orc.h"
#include "Merchant.h"
#include "Dragon.h"
#include "Potion.h"
#include "Gold.h"
#include "Stair.h"

#include <algorithm>    // std::shuffle
#include <stdexcept>    // std::runtime_error
#include <random>

static constexpr int NON_DRAGON_ENEMIES = 20;
static constexpr int POTION_COUNT       = 10;
static constexpr int GOLD_COUNT         = 10;

Level::Level(const std::string& mapPath, unsigned seed)
  : map(mapPath, seed),
    rng(seed),
    gameOver(false)
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
            if (t.isPassable() &&
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
        if (dynamic_cast<Dragon*>(uptr.get())) {
            auto dragon_hoard = std::make_unique<Gold>(4, true);
            t->setItem(dragon_hoard.get());
            itemStore.push_back(std::move(dragon_hoard));
        }
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

    for (int i = 0; i < GOLD_COUNT; ++i) {
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
    player = std::move(p);
    return true;
}

void get_xy(Direction dir, int& x, int& y) {
    switch (dir) {
        case Direction::North:
            x = -1;
            y = 0;
            break;
        case Direction::South:
            x = 1;
            y = 0;
            break;
        case Direction::East:
            x = 0;
            y = 1;
            break;
        case Direction::West:
            x = 0;
            y = -1;
            break;  
        case Direction::NorthEast:
            x = -1;
            y = 1;
            break;
        case Direction::NorthWest:
            x = -1; 
            y = -1;
            break;
        case Direction::SouthEast:
            x = 1;
            y = 1;
            break;
        case Direction::SouthWest:
            x = 1;
            y = -1;
            break;
        default:
            break;
    }
}

void Level::playerMove(Direction dir) {
    int x, y;
    get_xy(dir, x, y);
    player->move(x, y);
}

void Level::playerAttack(Direction dir) {
    int x, y;
    get_xy(dir, x, y);
    Tile& character_tile = map.getTile(player->getPosition().first + x, player->getPosition().second + y);
    Character* enemy = character_tile.getCharacter();
    if (enemy != nullptr) {
        enemy->beAttackedBy(player.get());
    }
}

void Level::playerPotion(Direction dir) {
    int x, y;
    get_xy(dir, x, y);
    Tile potion_tile = map.getTile(player->getPosition().first + x, player->getPosition().second + y);
    Item* item = potion_tile.getItem();
    if (item->isPotion()) {
        item->use(*player);
        delete item;
    }
}

void Level::placeGold(int value, Tile& tile) {
    auto g = std::make_unique<Gold>(value, false);
    tile.setItem(g.get());
    itemStore.push_back(std::move(g));
}



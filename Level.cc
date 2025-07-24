#include "Level.h"

#include <vector>
#include <memory>

using namespace std;

static constexpr int TOTAL_ENEMIES    = 21;  // including Dragon
static constexpr int POTION_COUNT     = 10;
static constexpr int TREASURE_COUNT   = 10;

Level::Level(const std::string& mapPath, unsigned seed): map(mapPath, seed), rng(seed) {
  generateEnemies(seed);

    // 2) Compute how many distinct tiles we need:
    //    1 PC + 1 stair + 21 enemies + 10 potions + 10 treasures
    size_t total = 1 + 1 + TOTAL_ENEMIES + POTION_COUNT + TREASURE_COUNT;

    // 3) Sample exactly 'total' unique passable tiles
    auto spots = samplePassableTiles(total);
    size_t idx = 0;

    // 4) Place the PC
    {
        Tile* t = spots[idx++];
        player = Player::create(chosenRace);
        t->setCharacter(pc.get());
    }

    // 5) Place the staircase
    {
        Tile* t = spots[idx++];
        staircase = std::make_unique<Staircase>();
        t->setItem(staircase.get());
    }

    // 6) Place all enemies
    for (int i = 0; i < TOTAL_ENEMIES; ++i) {
        Tile* t = spots[idx++];
        t->setCharacter(enemies[i].get());
    }

    // 7) Place potions
    for (int i = 0; i < POTION_COUNT; ++i) {
        Tile* t = spots[idx++];
        auto p = std::make_unique<Potion>();
        t->setItem(p.get());
        potions.push_back(std::move(p));
    }

    // 8) Place treasures
    for (int i = 0; i < TREASURE_COUNT; ++i) {
        Tile* t = spots[idx++];
        auto g = std::make_unique<Treasure>();
        t->setItem(g.get());
        treasures.push_back(std::move(g));
    }
}


void Level::generateEnemies(unsigned seed) {
    rng.seed(seed);

    // Roll a 1..18 “d18” to pick each non‐dragon enemy by weight:
    //  1–4   = Human (4)
    //  5–7   = Dwarf (3)
    //  8–12  = Halfling (5)
    //  13–14 = Elf (2)
    //  15–16 = Orc (2)
    //  17–18 = Merchant (2)
    uniform_int_distribution<int> roll(1, 18);

    for (int i = 0; i < 20; ++i) {
        int r = roll(rng);
        unique_ptr<Character> e;

        if      (r <=  4) e = make_unique<Human>();
        else if (r <=  7) e = make_unique<Dwarf>();
        else if (r <= 12) e = make_unique<Halfling>();
        else if (r <= 14) e = make_unique<Elf>();
        else if (r <= 16) e = make_unique<Orc>();
        else              e = make_unique<Merchant>();

        enemies.push_back(std::move(e));
    }

    // Always include one Dragon
    enemies.push_back(make_unique<Dragon>());
}

vector<Tile*> Level::samplePassableTiles(size_t N) {
    vector<Tile*> tiles;
    int W = map.getWidth(), H = map.getHeight();
    tiles.reserve(W * H);
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            Tile & t = map.getTile(x,y);
            if (t.isPassable()) tiles.push_back(&t);
        }
    }

    if (N > tiles.size()) {
        throw runtime_error("Not enough passable tiles");
    }

    shuffle(tiles.begin(), tiles.end(), rng);
    tiles.resize(N);
    return tiles;
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
    Tile character_tile = map.getTile(player->getPosition().first + x, player->getPosition().second + y);
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



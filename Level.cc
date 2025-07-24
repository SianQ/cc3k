#include "Level.h"

#include <vector>
#include <memory>

using namespace std;

void Level::generateEnemies(unsigned seed) {
    // Reseed our RNG so that generation is reproducible
    rng.seed(seed);

    // Roll a 1..18 “d18” to pick each non‐dragon enemy by weight:
    //  1–4   = Human (4)
    //  5–7   = Dwarf (3)
    //  8–12  = Halfling (5)
    //  13–14 = Elf (2)
    //  15–16 = Orc (2)
    //  17–18 = Merchant (2)
    std::uniform_int_distribution<int> roll(1, 18);

    for (int i = 0; i < 20; ++i) {
        int r = roll(rng);
        std::unique_ptr<Character> e;

        if      (r <=  4) e = make_unique<Human>();
        else if (r <=  7) e = make_unique<Dwarf>();
        else if (r <= 12) e = make_unique<Halfling>();
        else if (r <= 14) e = make_unique<Elf>();
        else if (r <= 16) e = make_unique<Orc>();
        else              e = make_unique<Merchant>();

        enemies.push_back(std::move(e));
    }

    // Always include one Dragon
    enemies.push_back(std::make_unique<Dragon>());
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



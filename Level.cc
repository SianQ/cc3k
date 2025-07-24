#include "Level.h"

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
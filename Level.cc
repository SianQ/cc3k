#include "Level.h"

void Level::playerMove(Direction dir) {
    switch (dir) {
        case Direction::North:
            player->move(-1, 0);
            break;
        case Direction::South:
            player->move(1, 0);
            break;
        case Direction::East:
            player->move(0, 1);
            break;
        case Direction::West:
            player->move(0, -1);
            break;
        case Direction::NorthEast:
            player->move(-1, 1);
            break;
        case Direction::NorthWest:
            player->move(-1, -1);
            break;
        case Direction::SouthEast:  
            player->move(1, 1);
            break;
        case Direction::SouthWest:
            player->move(1, -1);
            break;
        default:
            break;
    }
}

void Level::playerAttack(Direction dir) {
    int a, b;
    switch (dir) {
        case Direction::North:
            a = -1;
            b = 0;
            break;
        case Direction::South:
            a = 1;
            b = 0;
            break;
        case Direction::East:
            a = 0;
            b = 1;
            break;
        case Direction::West:
            a = 0;
            b = -1;
            break;  
        case Direction::NorthEast:
            a = -1;
            b = 1;
            break;
        case Direction::NorthWest:
            a = -1; 
            b = -1;
            break;
        case Direction::SouthEast:
            a = 1;
            b = 1;
            break;
        case Direction::SouthWest:
            a = 1;
            b = -1;
            break;
        default:
            break;
    }
    Tile character_tile = map.getTile(player->getPosition().first + a, player->getPosition().second + b);
    Character* enemy = character_tile.getCharacter();
    if (enemy != nullptr) {
        enemy->beAttackedBy(player);
    }
}

void Level::playerPotion(Direction dir) {
    // TODO: Implement player potion
}
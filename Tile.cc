#include "Tile.h"
#include "Character.h"

Tile::Tile()
  : terrain(TerrainType::Empty),
    character(nullptr),
    item(nullptr),
    x(-1),
    y(-1)
{}

Character* Tile::getCharacter() const {
    return character;
}

void Tile::setCharacter(Character* character) {
    this->character = character;
}

Item* Tile::getItem() const {
    return item;
}

void Tile::setItem(Item* item) {
    this->item = item;
}

TerrainType Tile::getTerrain() const {
    return terrain;
}

void Tile::setTerrain(TerrainType t) {
    terrain = t;
}

int Tile::getX() {
    return x;
}

void Tile::setX(int x) {
    this->x = x;
}

int Tile::getY() {
    return y;
}

void Tile::setY(int y) {
    this->y = y;
}

bool Tile::isPassable() const {
    bool walkableTerrain = 
        terrain == TerrainType::Floor ||
        terrain == TerrainType::Passage ||
        terrain == TerrainType::Door;
    bool emptyOfCharacters = (getCharacter() == nullptr);

    return walkableTerrain && emptyOfCharacters;
}

bool Tile::canSpawn() const {
    bool walkableTerrain = 
        terrain == TerrainType::Floor;
    bool emptyOfCharacters = (getCharacter() == nullptr);

    return walkableTerrain && emptyOfCharacters;
}


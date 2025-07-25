#include "Tile.h"
#include "Character.h"

Tile::Tile()
  : terrain(TerrainType::Empty),
    character(nullptr),
    item(nullptr)
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

bool Tile::isPassable() const {
    bool walkableTerrain = 
        terrain == TerrainType::Floor ||
        terrain == TerrainType::Passage;
    bool emptyOfCharacters = (getCharacter() == nullptr);

    return walkableTerrain && emptyOfCharacters;
}

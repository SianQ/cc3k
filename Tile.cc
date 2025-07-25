#include "Tile.h"
#include "Character.h"

Character* Tile::getCharacter() const {
    return charater;
}

void Tile::setCharacter(Character* character) {
    this->charater = character;
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

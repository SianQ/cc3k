// export module Tile;

// import Character;
// import Item;

#pragma once
#include "Character.h"
#include "Item.h"
#include "TerrainType.h"

// export
class Tile {
private:
    TerrainType terrain;
    Character* charater;
    Item* item;

public:
    Tile();
    Character* getCharacter();
    void setCharacter(Character* character);
    Item* getItem();
    void setItem(Item* item);
    TerrainType getTerrain();
    void setTerrain(TerrainType terrain);
    bool isPassable();
};

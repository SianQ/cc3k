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
    Character* character;
    Item* item;
    int x;
    int y;

public:
    Tile();
    
    Character* getCharacter() const;
    void setCharacter(Character* character);

    Item* getItem() const;
    void setItem(Item* item);

    TerrainType getTerrain() const;
    void setTerrain(TerrainType terrain);

    int getX();
    void setX(int x);

    int getY();
    void setY(int y);

    bool isPassable() const;
    bool canSpawn() const;
};

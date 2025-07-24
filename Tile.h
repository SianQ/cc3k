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
    
    Character* getCharacter() const;
    void setCharacter(Character* character);

    Item* getItem() const;
    virtual bool isGold();
    virtual bool isPotion();
    virtual bool isStair();
    void setItem(Item* item);

    TerrainType getTerrain() const;
    void setTerrain(TerrainType terrain);

    bool isPassable();
};

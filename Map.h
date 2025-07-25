// export module Map;

// import Tile;

// export
#pragma once
#include "Tile.h"
#include <vector>

class Map {
private:
    int width;
    int height;
    std::vector<Tile> grid;
public:
    Map(std::string mapPath, int seed);
    int getWidth() const;
    int getHeight() const;
    Tile& getTile(int x, int y) const;
    bool isPassible(int x, int y) const;
    bool canSpawn(int x, int y) const;
    void moveCharacter(int fromX, int fromY, int toX, int toY);
    void clearTile(int x, int y);
    bool inBounds(int x, int y) const;
};

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
    Map(int width, int height);
    Tile& getTile(int x, int y);
    bool isPassible(int x, int y);
    void moveCharacter(int fromX, int fromY, int toX, int toY);
};

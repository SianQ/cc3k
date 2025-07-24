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
    // void detectAroundPlayer(unique_ptr<Player> player, std::vector<Tile>& grid);
    // 1. eat potion
    // 2. pick up gold
    // 3. player attack (one choosen enemy; call enemy.beAttackedBy(player))
    // 4. call player.beAttackedBy(enemy)
};

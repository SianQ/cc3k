// Map.cpp

#include "Map.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"

#include <vector>

void Map::detectAroundPlayer(std::unique_ptr<Player> player,
                             std::vector<Tile>& grid) {
    // get player position directly from its fields
    int row = player->row;
    int col = player->col;

    // 1. Player uses a potion on their current tile, if any
    {
        Tile& t = getTile(row, col);
        if (t.hasPotion()) {
            Potion* pot = t.getPotion();       // assume Tile provides this
            player->usePotion(pot);
            t.removePotion();                  // assume Tile provides this
        }
    }

    // 2. Player picks up any gold on their current tile
    {
        Tile& t = getTile(row, col);
        if (t.hasGold()) {
            Gold* g = t.getGold();             // assume Tile provides this
            player->pickUpGold(g);
            t.removeGold();                    // assume Tile provides this
        }
    }

    // 3. Player attacks a chosen enemy (selection logic lives elsewhere)
    {
        // TODO: command-processing code will decide targetRow, targetCol
        // int targetRow = …;
        // int targetCol = …;
        // if valid:
        //   Tile& targetTile = getTile(targetRow, targetCol);
        //   if (targetTile.hasEnemy()) {
        //       Enemy* target = targetTile.getEnemy();
        //       target->beAttackedBy(player.get());
        //   }
    }

    // 4. All hostile enemies in the four adjacent tiles attack the player
    static const int drow[4] = { -1, 1,  0,  0 };
    static const int dcol[4] = {  0, 0, -1,  1 };
    for (int i = 0; i < 4; ++i) {
        int r = row + drow[i];
        int c = col + dcol[i];

        if (r < 0 || r >= height || c < 0 || c >= width) continue;

        Tile& t = getTile(r, c);
        if (t.hasEnemy()) {
            Enemy* e = t.getEnemy();
            player->beAttackedBy(e);
        }
    }

    // (Optional) fill 'grid' for rendering the 3×3 view around the player
    grid.clear();
    grid.reserve(9);
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int rr = row + dy, cc = col + dx;
            if (rr >= 0 && rr < height && cc >= 0 && cc < width) {
                grid.push_back(getTile(rr, cc));
            } else {
                grid.emplace_back(); // default‐constructed Tile (e.g. wall)
            }
        }
    }
}

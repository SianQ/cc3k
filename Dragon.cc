#include "Dragon.h"
#include "Map.h"
#include "Map.h"
#include "Tile.h"
#include "Gold.h"
#include <cstdlib>

Dragon::Dragon()
    : Enemy(150, 20, 20, "D", true, true), hoard(nullptr) {}

void Dragon::act(Map &map, Player &pc)
{
    // Check 4 adjacent cells around dragon (up, down, left, right only)
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < 4; ++i)
    {
        int nr = row + directions[i][0];
        int nc = col + directions[i][1];
        if (!map.isPassible(nr, nc))
            continue;
        if (map.getTile(nr, nc).getCharacter()->isPlayer())
        {
            attack(pc);
            return;
        }
    }

    // Check if player is adjacent to any guarded gold (dragon's hoard)
    auto playerPos = pc.getPosition();
    int playerRow = playerPos.first;
    int playerCol = playerPos.second;

    for (int i = 0; i < 4; ++i)
    {
        int nr = playerRow + directions[i][0];
        int nc = playerCol + directions[i][1];
        if (!map.isPassible(nr, nc))
            continue;

        // Check if this tile has a guarded gold item
        Item *item = map.getTile(nr, nc).getItem();
        if (item != nullptr && item->isGold())
        {
            Gold *gold = static_cast<Gold *>(item);
            if (gold->isGuarded())
            {
                attack(pc);
                return;
            }
        }
    }

    // Dragons never move
}

void Dragon::setHoard(Tile *tile)
{
    hoard = tile;
}

void Dragon::attack(Player &pc)
{
    pc.beAttackedBy(this);
}

void Dragon::dropLoot(Level &level, Map &map) const
{
    // Hoard is pre-placed; no drop here
    return;
}

#include "Dragon.h"
#include "Tile.h"
#include <cstdlib>

Dragon::Dragon()
    : Enemy(150, 20, 20, "D", true, true), hoard(nullptr) {}

// void Dragon::act(Map &map, Player &pc, Level &level)
// {

// }

void Dragon::attack(Player &pc, bool isAttackSuccessful)
{
    if (isAttackSuccessful) {
        pc.beAttackedBy(this);
    }
}

void Dragon::setHoard(Tile *tile)
{
    hoard = tile;
}



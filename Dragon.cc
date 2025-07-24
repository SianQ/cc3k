#include "Dragon.h"
#include "Map.h"
#include "Map.h"
#include "Tile.h"
#include <cstdlib>

Dragon::Dragon(int row, int col)
  : Enemy(150,20,20,row,col,"D",true,true) {}

void Dragon::act(Map& Map, Player& pc) {
    for (int dr=-1; dr<=1; ++dr) for (int dc=-1; dc<=1; ++dc) {
        if (dr==0 && dc==0) continue;
        int nr=row+dr, nc=col+dc;
        if (!Map.isPassible(nr,nc)) continue;
        if (Map.getTile(nr,nc).getCharacter()->isPlayer()) {
            attack(pc);
            return;
        }
    }
    // Dragons never move
}

void Dragon::attack(Player& pc) {
    pc.beAttackedBy(this);
}

std::vector<Item*> Dragon::dropLoot() const {
    // Hoard is pre-placed; no drop here
    return {};
}

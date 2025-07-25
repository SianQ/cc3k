#include "Merchant.h"
#include <cstdlib>
#include "Player.h"
#include "Level.h"

bool Merchant::hostileAll = false;

Merchant::Merchant()
  : Enemy(30,70,5,"M",false,false) {}

// void Merchant::act(Map& map, Player& pc, Level& level) {
// }

void Merchant::attack(Player& pc, bool isAttackSuccessful) {
    if(!hostileAll) return;
    if (isAttackSuccessful) {
        pc.beAttackedBy(this);
    }
}

void Merchant::dropLoot(Level& level, Map& map) const {
    level.placeGold(2, map.getTile(row, col));
}

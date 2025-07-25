#include "Human.h"
#include "Level.h"

Human::Human()
  : Enemy(140,20,20,"H",true,false) {}

void Human::dropLoot(Level& level, Map& map) const {
    level.placeGold(2, map.getTile(x, y));
}
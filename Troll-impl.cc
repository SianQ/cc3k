module Troll;
import <algorithm>;
import Race;

Troll::Troll()
  : Player(Race::Troll,120,25,15) {}

void Troll::perTermEvent() {
    if (hp < maxHP) {
        hp = std::min(maxHP, hp + 5);
    }
}

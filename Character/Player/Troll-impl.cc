module Troll;

Troll::Troll()
  : Player(120,25,15,120,"Troll") {}

Troll::~Troll() {}

void Troll::perTermEvent() {
    if (hp < maxHP) {
        hp = std::min(maxHP, hp + 5);
    }
}

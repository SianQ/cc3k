module Troll;

Troll::Troll()
  : Player(120,25,15,120,"Troll") {}

Troll::~Troll() {}

std::string Troll::getRace() const {
    return "Troll";
}

module Vampire;

Vampire::Vampire()
  : Player(50,25,25,50,"Vampire") {}

Vampire::~Vampire() {}

std::string Vampire::getRace() const {
    return "Vampire";
}

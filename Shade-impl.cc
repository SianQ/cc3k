module Shade;

Shade::Shade()
  : Player(125,25,25,125,"Shade") {}

Shade::~Shade() {}

std::string Shade::getRace() const {
    return "Shade";
}

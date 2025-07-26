module Drow;

Drow::Drow()
  : Player(150,25,15,150,"Drow") {}

Drow::~Drow() {}

std::string Drow::getRace() const {
    return "Drow";
}

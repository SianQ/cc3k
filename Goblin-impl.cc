module Goblin;

Goblin::Goblin()
    : Player(110,15,20,110,"Goblin") {}

  Goblin::~Goblin() {}

std::string Goblin::getRace() const {
    return "Goblin";
}

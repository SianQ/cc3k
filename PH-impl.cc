module PH;

PH::PH(std::shared_ptr<Player> next)
: Decorator(next) {
    if (next->getRace() == "Drow") {
        next->setHP(next->getHP() - 15);
    } else {
        next->setHP(next->getHP() - 10);
    }
}

PH::~PH() = default;

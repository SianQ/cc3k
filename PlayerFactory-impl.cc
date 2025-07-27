module PlayerFactory;

std::unique_ptr<Player> createPlayer(const std::string& race) {
    if (race == "Shade") return std::make_unique<Shade>();
    if (race == "Drow") return std::make_unique<Drow>();
    if (race == "Vampire") return std::make_unique<Vampire>();
    if (race == "Troll") return std::make_unique<Troll>();
    if (race == "Goblin") return std::make_unique<Goblin>();
    return nullptr;
}

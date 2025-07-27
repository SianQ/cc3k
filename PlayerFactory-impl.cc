module PlayerFactory;
import Player;
import Shade;
import Vampire;
import Troll;
import Goblin;
import Drow;
import <memory>;

std::unique_ptr<Player> createPlayer(const std::string& race) {
    if (race == "Shade") {
        return std::make_unique<Shade>();
    } else if (race == "Vampire") {
        return std::make_unique<Vampire>();
    } else if (race == "Troll") {
        return std::make_unique<Troll>();
    } else if (race == "Goblin") {
        return std::make_unique<Goblin>();
    } else if (race == "Drow") {
        return std::make_unique<Drow>();
    }
    
    // 默认返回Shade
    return std::make_unique<Shade>();
}

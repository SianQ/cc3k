module Input;
import Level;
import Direction;
import <unordered_map>;
import <sstream>;

using namespace std;

static const std::unordered_map<std::string, Direction> dirMap = {
    {"no", Direction::North},
    {"so", Direction::South},
    {"ea", Direction::East},
    {"we", Direction::West},
    {"ne", Direction::NorthEast},
    {"nw", Direction::NorthWest},
    {"se", Direction::SouthEast},
    {"sw", Direction::SouthWest},
};

void Input::applyInput(Level & level) {
    while (true) {
        std::cout << "Enter command (no/so/ea/we/ne/nw/se/sw, a <dir>, u <dir>): ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            // EOF
            return;
        }

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if (cmd.empty()) {
            continue;
        }

        // Attack or Use-Potion: "a no" or "u so"
        if (cmd == "a" || cmd == "u") {
            std::string dirToken;
            if (!(iss >> dirToken)) {
                std::cout << "Please specify a direction after '"
                          << cmd << "' (no/so/ea/…).\n";
                continue;
            }
            auto it = dirMap.find(dirToken);
            if (it == dirMap.end()) {
                std::cout << "Unknown direction: '" << dirToken
                          << "'. Try again.\n";
                continue;
            }
            Direction d = it->second;
            if (cmd == "a")       level.playerAttack(d);
            else /* cmd == "u" */ level.playerPotion(d);
            break;  // valid attack/use, exit loop

        } else {
            // Movement commands: "no", "so", etc.
            auto it = dirMap.find(cmd);
            if (it == dirMap.end()) {
                std::cout << "Unknown command: '" << cmd
                          << "'. Try again.\n";
                continue;
            }
            level.playerMove(it->second);
            break;  // valid move, exit loop
        }
    }
}

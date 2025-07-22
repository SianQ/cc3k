// export module Player;

// export

#include "Drow.h"
#include "Vampire.h"
#include "Troll.h"
#include "Goblin.h"
#include "Shade.h"

#include <memory>
#include <string>
#include <vector>

class Player {
private:

public:
    inline static const std::vector<std::string> RaceNames = {
        "Shade",
        "Vampire",
        "Troll",
        "Goblin",
        "Drow"
    };

    static std::unique_ptr<Player> create(const std::string& race) {
        std::string key = race;
        if (key == "drow")    return std::make_unique<Drow>(new Drow());
        else if (key == "vampire") return std::make_unique<Vampire>(new Vampire());
        else if (key == "troll") return std::make_unique<Troll>(new Troll());
        else if (key == "goblin") return std::make_unique<Goblin>(new Goblin());
        else return std::make_unique<Shade>(new Shade());
    }
};

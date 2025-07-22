// export module Player;

// export


#include "Dwarf.h"
#include "Elf.h"
// TODO: 记得导入别的种族

#include <memory>
#include <string>
#include <vector>

class Player {
private:

public:
    inline static const std::vector<std::string> RaceNames = {
        "Human",
        "Dwarf",
        "Elf",
        "Orc",
        "Merchant"
    };

    static std::unique_ptr<Player> create(const std::string& race) {
        std::string key = race;
        if (key == "dwarf")    return std::make_unique<Dwarf>(new Dwarf());
        else if (key == "elf") return std::make_unique<Elf>(new Elf());
        // TODO: 加上别的玩家种族
    }
};

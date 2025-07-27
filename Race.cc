export module Race;

import <string>;

export enum class Race {
    Shade,
    Drow,
    Vampire,
    Troll,
    Goblin,
    Human,
    Dwarf,
    Elf,
    Orc,
    Merchant,
    Dragon,
    Halfling
};

export inline std::string toString(Race r) {
    switch (r) {
        case Race::Shade:     return "Shade";
        case Race::Drow:      return "Drow";
        case Race::Vampire:   return "Vampire";
        case Race::Troll:     return "Troll";
        case Race::Goblin:    return "Goblin";
        case Race::Human:     return "Human";
        case Race::Dwarf:     return "Dwarf";
        case Race::Elf:       return "Elf";
        case Race::Orc:       return "Orc";
        case Race::Merchant:  return "Merchant";
        case Race::Dragon:    return "Dragon";
        case Race::Halfling:  return "Halfling";
    }
    return "Unknown";
}

module Output;

import Item;
import Tile;
import Map;
import TerrainType;
import Character;

import <iostream>;

using namespace std;

static constexpr const char* RESET  = "\033[0m";
static constexpr const char* RED    = "\033[31m";
static constexpr const char* GREEN  = "\033[32m";
static constexpr const char* YELLOW = "\033[33m";
static constexpr const char* BLUE   = "\033[34m";

void Output::render(Level & level) {
    Map & m = level.getMap();
    int h = m.getHeight();
    int w = m.getWidth();

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            Tile & tile = m.getTile(x, y);

            // 1) Character first
            if (Character* c = tile.getCharacter()) {
                char sym = c->getSymbol();
                // Assume Character has isPlayer() to identify the PC
                if (c->isPlayer()) {
                    std::cout << BLUE << sym << RESET;
                } else {
                    std::cout << RED  << sym << RESET;
                }
                continue;
            }

            // 2) Then Item
            if (Item * it = tile.getItem()) {
                char sym = it->getSymbol();
                if (it->isStair()) {
                    // Staircase in blue
                    std::cout << BLUE   << sym << RESET;
                }
                else if (it->isPotion()) {
                    // Potions in green
                    std::cout << GREEN  << sym << RESET;
                }
                else if (it->isGold()) {
                    // Treasure in yellow
                    std::cout << YELLOW << sym << RESET;
                }
                else {
                    // any other item default color
                    std::cout << sym;
                }
                continue;
            }

            // 3) Otherwise, terrain
            switch (tile.getTerrain()) {
                case TerrainType::Floor:
                    std::cout << '.';
                    break;
                case TerrainType::Passage:
                    std::cout << '#';
                    break;
                case TerrainType::WallHorizontal:
                    std::cout << '-';
                    break;
                case TerrainType::WallVertical:
                    std::cout << '|';
                    break;
                case TerrainType::Door:
                    std::cout << '+';
                    break;
                case TerrainType::Empty:
                default:
                    std::cout << ' ';
                    break;
            }
        }
        std::cout << '\n';
    }

    cout << "Race: "   << level.getPlayerRace() << " ";
    cout << "Gold: "   << level.getPlayerGold() << endl;
    cout << "HP: "     << level.getPlayerHp()   << endl;
    cout << "Atk: "    << level.getPlayerAtk()  << endl;
    cout << "Def: "    << level.getPlayerDef()  << endl;
    cout << "Action: " << level.getMessage()    << endl;
}

void Output::clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}

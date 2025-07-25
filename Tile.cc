#include "Tile.h"
#include "Character.h"
#include "Map.h"
#include <fstream>
#include <string>
#include <stdexcept>

Map::Map(std::string mapPath, int seed): width(0), height(0) {
    std::ifstream ifs(mapPath);
    if (!ifs) {
        throw std::runtime_error("Failed to open map file: " + mapPath);
    }

    // 1) Read all lines
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(ifs, line)) {
        lines.push_back(line);
    }

    // 2) Determine dimensions
    height = static_cast<int>(lines.size());
    width  = static_cast<int>(lines[0].size());

    // 3) Populate grid row-by-row
    grid.clear();
    grid.reserve(width * height);

    for (int y = 0; y < height; ++y) {
        const auto& row = lines[y];
        for (int x = 0; x < width; ++x) {
            Tile tile;
            char c = row[x];

            // 4) Map characters to TerrainType
            switch (c) {
                case '.': 
                    tile.setTerrain(TerrainType::Floor); 
                    break;
                case '#': 
                    tile.setTerrain(TerrainType::Passage); 
                    break;
                case ' ': 
                    tile.setTerrain(TerrainType::Empty); 
                    break;
                case '+': 
                    tile.setTerrain(TerrainType::Door); 
                    break;
                case '-': 
                    tile.setTerrain(TerrainType::WallHorizontal); 
                    break;
                case '|': 
                    tile.setTerrain(TerrainType::WallVertical); 
                    break;
                default:
                    tile.setTerrain(TerrainType::Empty); 
            }

            grid.push_back(tile);
        }
    }
}

Character* Tile::getCharacter() const {
    return charater;
}

void Tile::setCharacter(Character* character) {
    this->charater = character;
}

Item* Tile::getItem() const {
    return item;
}

void Tile::setItem(Item* item) {
    this->item = item;
}

TerrainType Tile::getTerrain() const {
    return terrain;
}

void Tile::setTerrain(TerrainType t) {
    terrain = t;
}

bool Tile::isPassable() const {
    bool walkableTerrain = 
        terrain == TerrainType::Floor ||
        terrain == TerrainType::Passage;
    bool emptyOfCharacters = (getCharacter() == nullptr);

    return walkableTerrain && emptyOfCharacters;
}

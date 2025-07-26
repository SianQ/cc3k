module Map;
import <fstream>;
import <string>;
import <stdexcept>;
import <vector>;

using namespace std;

Map::Map(const std::string& mapPath, int seed): width(0), height(0) {
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
            tile.setX(x);
            tile.setY(y);

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

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

Tile& Map::getTile(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Map::getTile: coordinates out of bounds");
    }
    return const_cast<Tile&>( grid.at(y * width + x) );
}

bool Map::isPassible(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return false;
    Tile& t = getTile(x,y);
    return t.isPassable();
}

bool Map::canSpawn(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return false;
    Tile& t = getTile(x,y);
    return t.canSpawn();
}

void Map::moveCharacter(int fromX, int fromY, int toX, int toY) {
    Tile& src = getTile(fromX, fromY);
    Tile& dst = getTile(toX,   toY);

    Character* c = src.getCharacter();
    src.setCharacter(nullptr);

    dst.setCharacter(c);
    c->setPosition(dst.getX(), dst.getY());
}

void Map::clearItem(int x, int y) {
    Tile& t = getTile(x, y);
    t.setItem(nullptr);
}

void Map::clearCharacter(int x, int y) {
    Tile& t = getTile(x, y);
    t.setCharacter(nullptr);
}

bool Map::inBounds(int x, int y) const {
    return x >= 0 && y >= 0 && x < height && y < width;
}

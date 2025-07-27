module Map;
import TerrainType;
import <fstream>;
import <string>;
import <stdexcept>;
import <vector>;

using namespace std;

Map::Map(const std::string mapPath, int seed): width(0), height(0) {
    std::ifstream ifs(mapPath);
    if (!ifs) {
        throw std::runtime_error("Failed to open map file: " + mapPath);
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(ifs, line)) {
        lines.push_back(line);
    }

    height = static_cast<int>(lines.size());
    width  = static_cast<int>(lines[0].size());

    grid.clear();
    grid.reserve(width * height);

    for (int y = 0; y < height; ++y) {
        const auto& row = lines[y];
        for (int x = 0; x < width; ++x) {
            Tile tile;
            char c = row[x];
            tile.setX(x);
            tile.setY(y);

            switch (c) {
                case '.': tile.setTerrain(TerrainType::Floor); break;
                case '#': tile.setTerrain(TerrainType::Passage); break;
                case ' ': tile.setTerrain(TerrainType::Empty); break;
                case '+': tile.setTerrain(TerrainType::Door); break;
                case '-': tile.setTerrain(TerrainType::WallHorizontal); break;
                case '|': tile.setTerrain(TerrainType::WallVertical); break;
                default:  tile.setTerrain(TerrainType::Empty);
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

const Tile& Map::getTile(int x, int y) const {
    return grid.at(y * width + x);
}

Tile& Map::getTile(int r, int c) {
    return grid.at(r * width + c);
}

bool Map::isPassible(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return false;
    return getTile(x, y).isPassable();
}

bool Map::canSpawn(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return false;
    return getTile(x, y).canSpawn();
}

void Map::moveCharacter(int fromX, int fromY, int toX, int toY) {
    Tile& src = const_cast<Tile&>(getTile(fromX, fromY));
    Tile& dst = const_cast<Tile&>(getTile(toX, toY));

    Character* c = src.getCharacter();
    src.setCharacter(nullptr);
    dst.setCharacter(c);
    c->setPosition(dst.getX(), dst.getY());
}

void Map::clearItem(int x, int y) {
    Tile& t = const_cast<Tile&>(getTile(x, y));
    t.setItem(nullptr);
}

void Map::clearCharacter(int x, int y) {
    Tile& t = const_cast<Tile&>(getTile(x, y));
    t.setCharacter(nullptr);
}

bool Map::inBounds(int x, int y) const {
    return x >= 0 && y >= 0 && x < width && y < height;
}

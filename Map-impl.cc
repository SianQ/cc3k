module Map;
import TerrainType;
import <fstream>;
import <string>;
import <stdexcept>;
import <vector>;
import <iostream>;

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

Tile& Map::getTile(int x, int y) const {
    if (!inBounds(x, y)) {
        cerr << ("Tile coordinates out of bounds: (" + to_string(x) + ", " + to_string(y) + ")");
        return nullptr;
    }
    return grid.at(y * width + x);
}

const vector<typename Tile>& Map::getAdjacentTiles(int x, int y) const {
    if (!inBounds(x, y)) {
        err << ("Get adjacent tiles coordinates out of bounds: (" + to_string(x) + ", " + to_string(y) + ")");
        return {};
    }

    vector<Tile*> adjacentTiles;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            if (inBounds(x + dx, y + dy)) {
                adjacentTiles.push_back(&getTile(x + dx, y + dy));
            }
        }
    }
    return adjacentTiles;
}

bool Map::isPassible(int x, int y) const {
    if (!inBounds(x, y)) return false;
    return getTile(x, y).isPassable();
}

bool isEnemyPassable(int x, int y) const {
    if (!inBounds(x, y)) return false;
    return getTile(x, y).isEnemyPassable();
}


bool Map::isEnemyPassible(int x, int y) const {
    if (!inBounds(x, y)) return false;
    return getTile(x, y).isEnemyPassable();
}


bool Map::canSpawn(int x, int y) const {
    if (!inBounds(x, y)) return false;
    return getTile(x, y).canSpawn();
}

void Map::clearItem(int x, int y) {
    if (!inBounds(x, y)) {
        err << "Clear tile item coordinates out of bounds: (" + to_string(x) + ", " + to_string(y) + ")";
        return;
    }
    Tile& t = getTile(x, y);
    t.setItem(nullptr);
}

void Map::setItem(int x, int y, Item* item) {
    if (!inBounds(x, y)) {
        err << "Set tile item coordinates out of bounds: (" + to_string(x) + ", " + to_string(y) + ")";
        return;
    }
    Tile& t = getTile(x, y);
    t.setItem(item);
}

Item* Map::getItem(int x, int y) const {
    if (!inBounds(x, y)) {
        err << "Get tile item coordinates out of bounds: (" + to_string(x) + ", " + to_string(y) + ")";
        return nullptr;
    }
    Tile& t = getTile(x, y);
    return t.getItem();
}

void Map::clearCharacter(int x, int y) {
    if (!inBounds(x, y)) {
        err << "Clear tile character coordinates out of bounds: (" + to_string(x) + ", " + to_string(y) + ")";
        return;
    }
    Tile& t = getTile(x, y);
    t.setCharacter(nullptr);
}

void Map::setCharacter(int x, int y, Character* character) {
    if (!inBounds(x, y)) {
        err << "Set tile character coordinates out of bounds: (" + to_string(x) + ", " + to_string(y) + ")";
        return;
    }
    Tile& t = getTile(x, y);
    t.setCharacter(character);
}

Character* Map::getCharacter(int x, int y) const {
    if (!inBounds(x, y)) {
        err << "Get tile character coordinates out of bounds: (" + to_string(x) + ", " + to_string(y) + ")";
        return nullptr;
    }
    Tile& t = getTile(x, y);
    return t.getCharacter();
}

bool Map::inBounds(int x, int y) const {
    return x >= 0 && y >= 0 && x < width && y < height;
}

export module Map;

import Tile;
import Character;
import TerrainType;
import <vector>;
import <string>;
import <memory>;

export class Map {
private:
    int width;
    int height;
    std::vector<Tile> grid;
public:
    Map(std::string mapPath, int seed);
    int getWidth() const;
    int getHeight() const;
    const Tile& getTile(int x, int y) const;
    Tile& getTile(int r, int c);
    bool isPassible(int x, int y) const;
    bool canSpawn(int x, int y) const;
    void moveCharacter(int fromX, int fromY, int toX, int toY);
    void clearItem(int x, int y);
    void clearCharacter(int x, int y);
    bool inBounds(int x, int y) const;
};

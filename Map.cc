export module Map;

import Tile;
import Character;
import TerrainType;
import Item;
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
    Tile& getTile(int x, int y);
    std::vector<Tile*> getAdjacentTiles(int x, int y);
    bool isPassible(int x, int y);
    bool isEnemyPassible(int x, int y);
    bool canSpawn(int x, int y);
    void clearItem(int x, int y);
    void setItem(int x, int y, Item* item);
    Item* getItem(int x, int y);
    void clearCharacter(int x, int y);
    void setCharacter(int x, int y, Character* character);
    Character* getCharacter(int x, int y);
    bool inBounds(int x, int y) const;
};

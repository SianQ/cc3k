export module Map;

import Tile;
import Character;
import <vector>;
import <string>;
import <memory>;

export class Map {
private:
    std::vector<Tile> grid;
    int width, height;

public:
    Map(const std::string mapPath, int seed);
    ~Map();

    // Grid access
    Tile* getTile(int row, int col);
    const Tile* getTile(int row, int col) const;
    
    // Map operations
    bool isPassible(int row, int col) const;
    void moveCharacter(int fromRow, int fromCol, int toRow, int toCol);
    void clearTile(int row, int col);
    
    // Getters
    int getWidth() const;
    int getHeight() const;
    
    // Display
    void display() const;
};

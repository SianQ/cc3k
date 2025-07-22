// export module level;

// import Output;
// import Map;

// import <vector>;
// import <string>;

// export

#pragma once
#include "Map.h"

#include <vector>
#include <string>


class Level {
private:
    Map map;
    Player player;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;
    bool gameOver;
    std::string messageLog;

public:
    Level(std::string mapPath);
    bool isGameOver();
    void handleCommand(std::string command);
    void movePlayer(int dx, int dy);
    void update();
};

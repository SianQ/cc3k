// export module level;

// import Output;
// import Map;

// import <vector>;
// import <string>;

// export

#pragma once
#include "Map.h"

#include <memory>
#include <vector>
#include <string>

using namespace std;

class Level {
private:
    Map map;
    unique_ptr<Player> player;
    vector<Enemy*> enemies;
    vector<Item*> items;
    bool gameOver;
    string messageLog;

public:
    Level(std::string mapPath);
    void setPlayer(unique_ptr<Player> player);
    bool isGameOver();
    void handleCommand(string command);
    void movePlayer(int dx, int dy);
    void updateEnemies();
};

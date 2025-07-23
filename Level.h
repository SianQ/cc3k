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
#include "Player.h"
#include "Enemy.h"
#include "Item.h"

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
    void setEnemies(vector<unique_ptr<Enemy>> enemies);
    void setItems(vector<unique_ptr<Item>> items);
    bool isGameOver();
    void handleCommand(string command);
    void movePlayer(int dx, int dy);
    void updateEnemies();
};

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
#include "Direction.h"

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
    bool setPlayer(unique_ptr<Player> player);
    void setEnemies(vector<unique_ptr<Enemy>> enemies);
    void setItems(vector<unique_ptr<Item>> items);
    bool isGameOver();
    void clearLog();
    void appendMessage(const std::string& message);

    // Player logic
    void playerMove(Direction dir);
    void playerAttack(Direction dir);
    void playerPotion(Direction dir);

    // Enemy logic
    void updateEnemies();
};

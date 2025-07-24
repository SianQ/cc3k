// export module level;

// import Output;
// import Map;

// import <vector>;
// import <string>;

// export

#pragma once
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Direction.h"
#include "Level.h"
#include "Human.h"
#include "Dwarf.h"
#include "Halfling.h"
#include "Elf.h"
#include "Orc.h"
#include "Merchant.h"
#include "Dragon.h"

#include <memory>
#include <vector>
#include <string>
#include <random>

using namespace std;

class Level {
private:
    Map map;
    unique_ptr<Player> player;
    vector<Enemy*> enemies;
    bool gameOver;
    string messageLog;
    std::default_random_engine rng;

public:
    Level(std::string mapPath, int seed);
    bool setPlayer(unique_ptr<Player> player);
    void setEnemies(vector<unique_ptr<Enemy>> enemies);
    void setItems(vector<unique_ptr<Item>> items);
    const Player& getPlayer() const;
    const Map& getMap() const;
    const string getMessage() const;
    bool isGameOver();
    void clearLog();
    void appendMessage(const std::string& message);
    void generateEnemies(unsigned seed);


    // Player logic
    void playerMove(Direction dir);   
    void playerAttack(Direction dir);
    void playerPotion(Direction dir);

    // Enemy logic
    void updateEnemies();
};

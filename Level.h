#pragma once

#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Direction.h"
#include <memory>
#include <vector>
#include <string>
#include <random>

class Level {
private:
    Map                                   map;
    std::unique_ptr<Player>               player;
    std::vector<std::unique_ptr<Enemy>>   enemyStore;   // owns all Enemy objects
    std::vector<std::unique_ptr<Item>>    itemStore;    // owns all Item objects
    bool                                  gameOver;
    std::string                           messageLog;
    std::default_random_engine            rng;
    inline static int levelNum = 1;
    // [0]=PC, [1]=stair, [2..] everything else
    std::vector<Tile*>                    spawnSpots;

    // helpers for setup
    void generateEnemies(unsigned seed);
    std::vector<Tile*> samplePassableTiles(size_t N);
    void placeNonPlayerObjects();

public:
    /// Load terrain from `mapPath` and seed RNG with `seed`
    Level(const std::string& mapPath, unsigned seed);

    /// Once race is chosen, place the PC and return success
    bool spawnPlayer(const std::string& race);

    const Player&     getPlayer()  const;
    const Map&        getMap()     const;
    const std::string getMessage() const;
    bool              isGameOver() const;

    void clearLog();
    void appendMessage(const std::string& message);
    void placeGold(int value, Tile& tile);

    // Player actions
    void playerMove(Direction dir);
    void playerAttack(Direction dir);
    void playerPotion(Direction dir);

    // Enemy turn
    void updateEnemies();

};

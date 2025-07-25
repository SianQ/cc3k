#pragma once

#include "Character.h"
#include <string>
#include <vector>
#include "Map.h"
#include "Player.h"
#include "Level.h"

/**
 * Abstract base class for all enemies.
 * typeSymbol: one‐letter code (H, W, E, O, M, D, L).
 */
class Enemy : public Character {
protected:
    bool        hostile;   // whether this enemy attacks on sight
    bool        isDragon;  // dragons never move
    std::string type;      // symbol code
    bool isEnemyDead; 
    std::string race;

public:
    Enemy(int hp, int atk, int def,          
          const std::string& typeSymbol,
          bool hostile = true,
          bool isDragon = false,
          int row = -1, int col = -1);
    virtual ~Enemy() = default;

    // One turn of behavior: either attack or move
    virtual void act(Map& Map, Player& pc) = 0;

    // Perform the actual attack on the player
    virtual void attack(Player& pc) = 0;

    // What items this enemy drops when slain
    virtual void dropLoot(Level& level, Map& map) const;

    bool isHostile() const;
    void setHostile(bool h);
    bool dragon() const;
    virtual char getSymbol() const override;  
    virtual std::string getRace() const override;
};


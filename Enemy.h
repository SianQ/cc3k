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

public:
    Enemy(int hp, int atk, int def,
          int row, int col,
          const std::string& typeSymbol,
          bool hostile = true,
          bool isDragon = false);
    virtual ~Enemy() = default;

    // One turn of behavior: either attack or move
    virtual void act(Map& Map, Player& pc) = 0;

    // Perform the actual attack on the player
    virtual void attack(Player& pc) = 0;

    // What items this enemy drops when slain
    virtual std::vector<Item*> dropLoot() const = 0;

    // If a potion is thrown at this enemy
    virtual void usePotion(Potion* pot);

    bool isHostile() const;
    void setHostile(bool h);
    bool dragon() const;
    const std::string& getSymbol() const;
};

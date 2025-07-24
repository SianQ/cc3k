// Enemy.h
#pragma once

#include "Character.h"
#include <string>
#include <vector>

// Forward declarations
class Level;
class Player;
class Item;
class Potion;

/**
 * Abstract base class: all enemies inherit from Character
 * and must implement act() and dropLoot().
 */
class Enemy : public Character {
    public:
        Enemy(int x, int y,
            int hp, int atk, int def,
            const std::string &typeName,
            bool isDragon);

        ~Enemy() override = default;

        // Defines what the enemy does on its turn
        virtual void act(Level &level, Player &pc) = 0;

        // Returns items dropped when the enemy is killed
        virtual std::vector<Item*> dropLoot() const = 0;

        // Handle a potion thrown at this enemy
        virtual void usePotion(Potion* pot);

        bool              isHostile() const;
        void              setHostile(bool h);
        const std::string& getType() const;
        virtual int getAtk() const override;
        virtual int getDef() const override;
        virtual int getHP() const override;
        virtual char getSymbol() const override;

    protected:
        bool        hostile;    // whether the enemy will attack the player
        bool        isDragon;   // true if this enemy is a dragon
        std::string type;       // enemy type name
        bool isDead;

    friend class Level; // Allow Level to access private members
    friend class Player; // Allow Player to access private members
};

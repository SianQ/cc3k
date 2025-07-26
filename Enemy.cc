// export module Enemy;

// import Character;
// import <string>;

// export

import Character;
import Map;
import Player;
import Level;
import <string>;

export class Enemy : public Character {
protected:
    bool        hostile;   // whether this enemy attacks on sight
    bool        isDragon;  // dragons never move
    std::string type;      // symbol code
    std::string race;
    bool        deathProcessed = false; // whether death cleanup has been done

public:
    Enemy(int hp, int atk, int def,          
          const std::string& typeSymbol,
          bool hostile = true,
          bool isDragon = false,
          int x = -1, int y = -1);
    virtual ~Enemy() = default;

    // One turn of behavior: either attack or move
    virtual void act(Map& map, Player& pc, Level& level);

    // Perform the actual attack on the player
    virtual void attack(Player& pc, bool isAttackSuccessful, Level& level);
    int beAttackedBy(Character* attacker) override;

    // What items this enemy drops when slain
    virtual void dropLoot(Level& level, Map& map) const;

    bool isHostile() const;
    void setHostile(bool h);
    virtual char getSymbol() const override;  
    virtual std::string getRace() const override;
};


export module GameCore;

import Character;
import Player;
import Map;
import Tile;
import Item;
import Gold;
import Potion;
import Stair;
import Direction;
import PotionType;
import <string>;
import <vector>;
import <memory>;
import <random>;
import <utility>;
import <algorithm>;
import <cmath>;
import <sstream>;

// ========== Forward Declarations ==========
export class Level;
export class Enemy;

// ========== Enemy Base Class ==========
export class Enemy : public Character {
protected:
    bool hostile;
    bool isDragon;
    std::string type;
    std::string race;
    bool deathProcessed = false;

public:
    Enemy(int hp, int atk, int def, const std::string& typeSymbol,
          const std::string& raceName, bool hostile = true,
          bool isDragon = false, int x = -1, int y = -1);
    virtual ~Enemy() = default;

    virtual void act(Map& map, Player& pc, Level& level);
    virtual void attack(Player& pc, bool isAttackSuccessful, Level& level);
    int beAttackedBy(Character* attacker) override;
    virtual void dropLoot(Level& level, Map& map) const;

    bool isHostile() const;
    void setHostile(bool h);
    char getSymbol() const override;
    std::string getRace() const override;
};

// ========== Enemy Subclasses ==========
export class Human : public Enemy {
public:
    Human();
    void dropLoot(Level& level, Map& map) const override;
};

export class Dwarf : public Enemy {
public:
    Dwarf();
};

export class Merchant : public Enemy {
    static bool hostileAll;
public:
    Merchant();
    void attack(Player& pc, bool isAttackSuccessful, Level& level) override;
    void dropLoot(Level& level, Map& map) const override;
    int beAttackedBy(Character* attacker) override;
};

export class Dragon : public Enemy {
    Tile* hoard;
public:
    Dragon();
    void act(Map& map, Player& pc, Level& level) override;
    int beAttackedBy(Character* attacker) override;
    void setHoard(Tile* tile);
};

export class Halfling : public Enemy {
public:
    Halfling();
};

export class Orc : public Enemy {
public:
    Orc();
};

export class Elf : public Enemy {
public:
    Elf();
    void attack(Player& pc, bool isAttackSuccessful, Level& level) override;    
};


// ========== Level Class ==========
export class Level {
private:
    Map map;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::default_random_engine rng;
    std::vector<std::string> messages;
    int floorNumber;
    bool gameComplete;

public:
    Level(const std::string& mapFile, int seed, int floor);
    ~Level() = default;

    void playerMove(Direction dir);
    void playerAttack(Direction dir);
    void playerPotion(Direction dir);
    void updateEnemies();

    Direction randomDir();
    bool isAttackSuccess();

    void appendMessage(const std::string& msg);
    std::vector<std::string> getMessages() const;
    void clearMessages();

    const Map& getMap() const;
    const Player& getPlayer() const;
    Player& getPlayer();
    bool isGameComplete() const;
    int getFloorNumber() const;

    void placeGold(int value, Tile& tile);
    void placePotion(PotionType type, Tile& tile);
    void placeStairs(Tile& tile);
    std::pair<int, int> directionToDelta(Direction dir);
};

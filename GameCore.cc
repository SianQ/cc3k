export module GameCore;

import Character;
import Player;
import Map;
import Tile;
import Item;
import Gold;
import Potion;
import Direction;
import PotionType;
import <string>;
import <vector>;
import <memory>;
import <random>;
import <utility>;
import <iostream>;
import <fstream>;

// ========== 前向声明 ==========
export class Level;
export class Enemy;

// ========== Enemy基类 ==========
export class Enemy : public Character {
protected:
    bool hostile;
    bool isDragon;
    std::string type;
    bool deathProcessed = false;

public:
    Enemy(int hp, int atk, int def, const std::string& typeSymbol,
          bool hostile = true, bool isDragon = false, int x = -1, int y = -1);
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

// ========== Enemy子类们 ==========
export class Human : public Enemy {
public:
    Human();
    void dropLoot(Level& level, Map& map) const override;
};

export class Dwarf : public Enemy {
public:
    Dwarf();
};

export class Elf : public Enemy {
public:
    Elf();
    void attack(Player& pc, bool isAttackSuccessful, Level& level) override;
};

export class Orc : public Enemy {
public:
    Orc();
};

export class Halfling : public Enemy {
public:
    Halfling();
};

export class Goblin : public Enemy {
public:
    Goblin();
};

export class Troll : public Enemy {
public:
    Troll();
    void attack(Player& pc, bool isAttackSuccessful, Level& level) override;
};

export class Vampire : public Enemy {
public:
    Vampire();
    void attack(Player& pc, bool isAttackSuccessful, Level& level) override;
};

export class Merchant : public Enemy {
public:
    Merchant();
    void attack(Player& pc, bool isAttackSuccessful, Level& level) override;
    void dropLoot(Level& level, Map& map) const override;
};

export class Dragon : public Enemy {
public:
    Dragon();
    void act(Map& map, Player& pc, Level& level) override;
};

// ========== Level类 ==========
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
    
    // 游戏逻辑
    void playerMove(Direction dir);
    void playerAttack(Direction dir);
    void playerUsePotion(Direction dir);
    void updateEnemies();
    
    // 随机数生成
    Direction randomDir();
    bool isAttackSuccess();
    
    // 消息系统
    void appendMessage(const std::string& msg);
    std::vector<std::string> getMessages() const;
    void clearMessages();
    
    // 访问器
    const Map& getMap() const;
    const Player& getPlayer() const;
    Player& getPlayer();
    bool isGameComplete() const;
    int getFloorNumber() const;
    
    // 游戏状态管理
    void placeGold(int value, Tile* tile);
    void placePotion(PotionType type, Tile* tile);
    void placeStairs(Tile* tile);
};

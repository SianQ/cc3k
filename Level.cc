export module Level;
import Map;
import Player;
import Enemy;
import Item;
import Direction;
import Tile;
import Potion;
import Decorator;
import <memory>;
import <vector>;
import <string>;
import <random>;

export class Level {
private:
    Map                                   map;
    std::shared_ptr<Player>               player;
    std::vector<std::unique_ptr<Enemy>>   enemyStore;   // owns all Enemy objects
    std::vector<std::unique_ptr<Item>>    itemStore;    // owns all Item objects
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
    bool isFinished() const;
    bool isGameOver() const;
    bool isGameComplete() const;

    Level(const std::string& mapPath, unsigned seed);

    /// Once race is chosen, place the PC and return success
    bool spawnPlayer(const std::string& race);

    bool isAttackSuccess();
    Direction randomDir();

    const Player&     getPlayer()  const;
    const Map&        getMap()     const;
    const std::string getMessage() const;

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

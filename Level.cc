export module Level;
import Map;
import Player;
import Enemy;
import Item;
import Direction;
import <memory>;
import <vector>;
import <string>;
import <random>;

export class Level {
private:
    inline static int levelNum = 1;
    Map                                   map;
    std::shared_ptr<Player>               player;
    std::vector<std::unique_ptr<Enemy>>   enemyStore;   // owns all Enemy objects
    std::vector<std::unique_ptr<Item>>    itemStore;    // owns all Item objects
    std::string                           messageLog;
    std::default_random_engine            rng;
    std::vector<Tile*>                    spawnSpots;

    bool levelFinished = false;

    void generateEnemies(unsigned seed);
    std::vector<Tile*> samplePassableTiles(size_t N);
    void placeNonPlayerObjects();

    void appendMessage(const std::string& message);

    bool isAttackSuccess();
    Direction randomDir();

    Tile& getDirTile(Character& character, Direction dir) const;
    bool moveCharacter(Character& character, Direction dir);
    bool moveEnemy(Character& enemy, Direction dir);

    void placeGold(int value, Tile& tile);
    void pickUpGold();

    void playerMove(Direction dir);
    void playerAttack(Direction dir);
    void playerPotion(Direction dir);

    void updateEnemies();

    
public:
    Level(const std::string& mapPath, unsigned seed);

    // Game status
    bool isFinished() const;
    bool isGameOver() const;
    bool isGameComplete() const;

    // Add player
    void spawnPlayer(const std::string& race);

    // Logs
    const std::string getMessage() const;
    void clearLog();

    void perTermEvent();
};

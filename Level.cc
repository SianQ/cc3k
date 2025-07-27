export module Level;
import Map;
import Player;
import Enemy;
import Item;
import Direction;
import Tile;
import Character;
import Race;
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

    Tile& getDirTile(Character& character, Direction dir);
    bool moveCharacter(Character& character, Direction dir);
    bool moveEnemy(Character& enemy, Direction dir);

    void placeGold(int value, Tile& tile);
    void giveRandomGold();
    void pickUpGold();

    
public:
    Level(const std::string& mapPath, unsigned seed);

    // Game status
    bool isFinished();
    bool isGameOver();
    bool isGameComplete();

    std::string getPlayerRace();
    int getPlayerHp() const;
    int getPlayerAtk() const;
    int getPlayerDef() const;
    int getPlayerGold() const;
    Map& getMap();

    // Add player
    std::shared_ptr<Player> create(Race race);
    void spawnPlayer(const Race race);

    // Logs
    const std::string getMessage() const;
    void clearLog();
    
    void playerMove(Direction dir);
    void playerAttack(Direction dir);
    void playerPotion(Direction dir);

    void updateEnemies();

    void perTermEvent();
};

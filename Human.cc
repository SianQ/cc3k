export module Human;
import LevelFwd;
import Enemy;
import Map;

export class Human : public Enemy {
public:
    Human();
    void dropLoot(Level& level, Map& map) const override;
};

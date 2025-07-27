export module Human;
import Enemy;
import Level; 
import Map;

export class Human : public Enemy {
public:
    Human();
    void dropLoot(Level& level, Map& map) const override;
};

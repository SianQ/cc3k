export module Human;
import Enemy;

export class Human : public Enemy {
public:
    Human();
    void dropLoot(Level& level, Map& map) const override;
};

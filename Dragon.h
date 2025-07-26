export module Dragon;
import Character;
import Enemy;
import Map;
import Level;
import Tile;

export class Dragon : public Enemy {
    Tile* hoard;
public:
    Dragon();
    void setHoard(Tile* tile);
    void act(Map &map, Player &pc, Level &level) override;
    int beAttackedBy(Character* attacker) override;
};

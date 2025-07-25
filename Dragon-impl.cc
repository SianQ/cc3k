module Dragon;
import Tile;
import Map;
import Player;
import Level;
import Gold;
import <cstdlib>;

Dragon::Dragon()
    : Enemy(150, 20, 20, "D", true, true), hoard(nullptr) {}

void Dragon::act(Map &map, Player &pc, Level &level) {
    // If dead and haven't processed death yet, handle death cleanup
    if (this->isDead() && !deathProcessed) {
        map.clearCharacter(x, y);
        dropLoot(level, map);
        deathProcessed = true;
        return;
    }

    // If dead and already processed, do nothing
    if (this->isDead()) {
        return;
    }

    int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    // Check if player is adjacent to dragon
    for (int i = 0; i < 4; ++i) {
        int nr = x + directions[i][0];
        int nc = y + directions[i][1];
        if (!map.inBounds(nr, nc)) continue;
        if (!map.isPassible(nr, nc)) continue;

        Tile &tile = map.getTile(nr, nc);
        Character* c = tile.getCharacter();
        if (c != nullptr && c->isPlayer()) {
            attack(pc, level.isAttackSuccess(), level);
            return;
        }
    }

    // Check if player is adjacent to any guarded gold (dragon's hoard)
    auto playerPos = pc.getPosition();
    int playerx = playerPos.first;
    int playery = playerPos.second;

    for (int i = 0; i < 4; ++i) {
        int nr = playerx + directions[i][0];
        int nc = playery + directions[i][1];

        if (!map.inBounds(nr, nc)) continue;

        Tile &tile = map.getTile(nr, nc);
        Item* item = tile.getItem();
        if (item != nullptr && item->isGold()) {
            Gold* gold = static_cast<Gold*>(item);
            if (gold->isGuarded()) {
                attack(pc, level.isAttackSuccess(), level);
                return;
            }
        }
    }

    // Dragons never move (they are stationary)
}

int Dragon::beAttackedBy(Character* attacker) {
    int dmg = Enemy::beAttackedBy(attacker);
    if (this->isDead() && hoard != nullptr) {
        // Drop the hoard when the dragon is slain
        static_cast<Gold*>(hoard->getItem())->changeGuarded();
    }
    return dmg;
}

void Dragon::setHoard(Tile *tile)
{
    hoard = tile;
}



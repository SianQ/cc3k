#pragma once
#include "Dragon.h"
#include "Tile.h"
#include "Map.h"
#include "Player.h"
#include "Level.h"
#include "Gold.h"
#include <cstdlib>

Dragon::Dragon()
    : Enemy(150, 20, 20, "D", true, true), hoard(nullptr) {}

void Dragon::act(Map &map, Player &pc, Level &level) {
    if (this->isDead()) {
        // Clear the tile and drop loot when dead
        map.clearTile(x, y);
        dropLoot(level, map);
        return;
    }

    // Dragons check 4 adjacent cells around themselves first (up, down, left, right only)
    int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    // Check if player is adjacent to dragon
    for (int i = 0; i < 4; ++i) {
        int nr = x + directions[i][0];
        int nc = y + directions[i][1];
        if (!map.isPassible(nr,nc)) continue;
        if (map.getTile(nr,nc).getCharacter() != nullptr && 
            map.getTile(nr,nc).getCharacter()->isPlayer()) {
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
        if (map.isPassible(nr,nc)) continue;
        
        // Check if this tile has a guarded gold item
        Item* item = map.getTile(nr,nc).getItem();
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



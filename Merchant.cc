#pragma once
#include "Merchant.h"
#include "Map.h"
#include "Player.h"
#include "Level.h"
#include <cstdlib>

bool Merchant::hostileAll = false;

Merchant::Merchant()
  : Enemy(30,70,5,"M",false,false) {}

void Merchant::act(Map& map, Player& pc, Level& level) {
    if (this->isDead()) {
        // Clear the tile and drop loot when dead
        map.clearTile(x, y);
        dropLoot(level, map);
        return;
    }

    // Only act hostilely if hostileAll is true (after any merchant has been attacked)
    if (hostileAll) {
        // Check if the player is adjacent, if so, attack if isAttackSuccess is true
        if (std::abs(pc.getPosition().first - x) + std::abs(pc.getPosition().second - y) == 1) {
            attack(pc, level.isAttackSuccess(), level);
            return; // Don't move after attacking
        }
    }

    // Move randomly (both hostile and neutral merchants can move)
    // Use the same direction conversion as Enemy.cc
    auto dirToDelta = [](Direction d) -> std::pair<int,int> {
        switch (d) {
            case Direction::North: return {-1, 0};
            case Direction::South: return { 1, 0};
            case Direction::East:  return { 0, 1};
            case Direction::West:  return { 0,-1};
            default:               return { 0, 0}; 
        }
    };

    for (int tries = 0; tries < 4; ++tries) {
        Direction dir = level.randomDir();
        auto [dr, dc] = dirToDelta(dir);
        int nr = x + dr, nc = y + dc;
        if (map.isPassible(nr, nc)) { 
            map.moveCharacter(x, y, nr, nc);
            x = nr;
            y = nc;
            break;
        }
    }
}

void Merchant::attack(Player& pc, bool isAttackSuccessful, Level& level) {
    if(!hostileAll) return;
    if (isAttackSuccessful) {
        int damage = pc.beAttackedBy(this);
        if (damage > 0) {
            level.appendMessage("M deals " + std::to_string(damage) + " damage to PC.");
        }
    }
}

void Merchant::dropLoot(Level& level, Map& map) const {
    level.placeGold(2, map.getTile(x, y));
}

int Merchant::beAttackedBy(Character* attacker) {
    // When any merchant is attacked, all merchants become hostile
    if (attacker->isPlayer()) {
        hostileAll = true;
    }
    
    // Call parent's beAttackedBy to handle damage
    return Enemy::beAttackedBy(attacker);
}

#pragma once
#include "Merchant.h"
#include "Map.h"
#include "Player.h"
#include "Level.h"
#include <cstdlib>

bool Merchant::hostileAll = false;

Merchant::Merchant()
  : Enemy(30,70,5,"M",false,false) {}


void Merchant::attack(Player& pc, bool isAttackSuccessful, Level& level) {
    if(!hostileAll) return;
    if (isAttackSuccessful) {
        int damage = pc.beAttackedBy(this);
        if (damage > 0) {
            level.appendMessage("M deals " + std::to_string(damage) + " damage to PC.");
        }
    } else {
        level.appendMessage("M misses PC.");
    }
}

void Merchant::dropLoot(Level& level, Map& map) const {
    level.placeGold(2, map.getTile(x, y));
}

int Merchant::beAttackedBy(Character* attacker) {
    // When any merchant is attacked by player, all merchants become hostile
    if (attacker && attacker->isPlayer()) {
        hostileAll = true;
    }
    
    // Call parent's beAttackedBy to handle damage
    return Enemy::beAttackedBy(attacker);
}

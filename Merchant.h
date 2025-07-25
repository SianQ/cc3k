#pragma once
#include "Enemy.h"

/**
 * Merchant: HP=30, Atk=70, Def=5.
 * Neutral until one is attacked → all become hostile.
 * Drops one merchant hoard (4 gold).
 */
class Merchant : public Enemy {
public:
    Merchant();

    void act(Map& map, Player& pc, Level& level) override;
    void attack(Player& pc, bool isAttackSuccessful) override;
    void dropLoot(Level& level, Map& map) const override;

    static bool hostileAll;
};

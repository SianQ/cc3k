// export module Merchant;

// import Enemy;

// export
export module Merchant;
import Enemy;

/**
 * Merchant: HP=30, Atk=70, Def=5.
 * Neutral until one is attacked → all become hostile.
 * Drops one merchant hoard (4 gold).
 */
export class Merchant : public Enemy {
public:
    Merchant();

    void attack(Player& pc, bool isAttackSuccessful, Level& level) override;
    void dropLoot(Level& level, Map& map) const override;
    int beAttackedBy(Character* attacker) override;

    static bool hostileAll;
};

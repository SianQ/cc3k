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

    inline static bool hostileAll = false;

    bool isHostile();
    void setHostile(bool isHostile);

    void takeDamage(int damage, const Character* source) override;
};

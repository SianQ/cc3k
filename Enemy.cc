import Character;

export class Enemy : public Character {
protected:
    bool isLooted = false;

public:
    Enemy(Race race, int hp, int atk, int def);

    int attack(const Character* target, bool isSuccess) override;
    void takeDamage(int damage, const Character* source) override;
};


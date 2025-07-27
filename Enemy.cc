export module Enemy;

import Character;
import Race;

export class Enemy : public Character {
protected:
    bool isLooted = false;

public:
    Enemy(Race race, int hp, int atk, int def);

    int attack(Character* target, bool isSuccess);
    void takeDamage(int damage, const Character* source);
};


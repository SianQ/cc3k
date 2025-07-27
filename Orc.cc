export module Orc;
import Enemy;

export class Orc : public Enemy {
public:
    Orc();

    int attack(const Character* target, bool isSuccess) override;
};

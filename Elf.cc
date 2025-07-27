export module Elf;

import Enemy;

export class Elf : public Enemy {
public:
    Elf();
    int attack(Character* target, bool isSuccess) override;
};

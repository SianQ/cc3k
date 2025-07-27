export module Vampire;

import Player;

export class Vampire : public Player {
public:
    Vampire();
    ~Vampire() override;
    int attack(const Character* target) override;
};

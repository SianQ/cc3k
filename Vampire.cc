export module Vampire;

import Player;

export class Vampire : public Player {
public:
    Vampire();
    int attack(const Character* target) override;
};

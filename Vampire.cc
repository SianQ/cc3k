export module Vampire;

import Player;

export class Vampire : public Player {
public:
    Vampire();
    int attack(Character* target, bool isSuccess) override;
};

export module Vampire;

import Player;

export class Vampire : public Player {
public:
    Vampire();
    ~Vampire() override;
    std::string getRace() const override;
};


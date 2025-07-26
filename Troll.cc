export module Troll;

import Player;

export class Troll : public Player {
public:
    Troll();
    ~Troll() override;
    std::string getRace() const override;
};

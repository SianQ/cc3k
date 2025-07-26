export module Shade;

import Player;

export class Shade : public Player {
public:
    Shade();
    ~Shade() override;
    std::string getRace() const override;
};

export module Troll;

import Player;

export class Troll : public Player {
public:
    Troll();
    void perTermEvent() override;
};

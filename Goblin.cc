export module Goblin;
import Player;

export class Goblin : public Player {
public:
    Goblin();
    int attack(const Character* target) override;
};

export module Goblin;
import Player;

export class Goblin : public Player {
public:
    Goblin();
    int attack(Character* targe, bool isSuccess) override;
};

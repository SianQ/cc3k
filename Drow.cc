export module Drow;
import Player;
import Potion;

class Drow : public Player {
public:
    Drow();
    ~Drow() override;
    
    std::string getRace() const override;
};

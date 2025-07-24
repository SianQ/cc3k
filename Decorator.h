class CharacterDecorator : public Character {
    protected:
        std::shared_ptr<Character> base;
    
    public:
        CharacterDecorator(std::shared_ptr<Character> base) : Character(base->getHP(), base->getAtk(), base->getDef(), base->getPosition().first, base->getPosition().second), base{base} {}
        virtual ~CharacterDecorator() = default;
    
        // By default, just forward calls to the base
        int getAtk() const override { return base->getAtk(); }
        int getDef() const override { return base->getDef(); }
        int getHP() const override { return base->getHP(); }
        // void attack(Character* target) override { base->attack(target); }

        virtual isPlayer() = 0;
};

class BoostAtkDecorator : public CharacterDecorator {
    int boost;

public:
    BoostAtkDecorator(std::shared_ptr<Character> base, int amount)
        : CharacterDecorator(base), boost{amount} {}

    int getAtk() const override {
        return base->getAtk() + boost;
    }
};

class WoundDefDecorator : public CharacterDecorator {
    int penalty;

public:
    WoundDefDecorator(std::shared_ptr<Character> base, int amount)
        : CharacterDecorator(base), penalty{amount} {}

    int getDef() const override {
        return std::max(0, base->getDef() - penalty);
    }
};
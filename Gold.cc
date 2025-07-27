export module Gold;
import Item;

export class Gold : public Item{
private:
    int value;
    bool guardedByDragon;

public:
    Gold(int value, bool guarded);

    char getSymbol() const override;

    bool isGold() override;

    // Amount of gold to add
    int getValue() const;

    // Whether this gold is guarded by a dragon
    bool isGuarded() const;

    void setGuarded(bool guarded);
};

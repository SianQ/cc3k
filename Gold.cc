export module Gold;
import Item;
import Character;
import <string>;

/**
 * Gold: when picked up, gives currency to the consumer.
 * If guardedByDragon == true, it cannot be picked up.
 */
export class Gold : public Item
{
public:
    Gold(int value, bool guarded);

    // Returns "Gold" or a formatted display name
    char getSymbol() const override;

    // Override pure virtual functions from Item
    bool isGold() override;
    bool isPotion() override;
    bool isStair() override;

    // Amount of gold to add
    int getValue() const;

    // Whether this gold is guarded by a dragon
    bool isGuarded() const;

    void changeGuarded();

private:
    int value;
    bool guardedByDragon;
};

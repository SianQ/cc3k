#include "Potion.h"
#include "Character.h"

class RestoreHealthPotion : public Potion {
public:
    void use(Character& target) override;
    PotionType getType() const override;
};

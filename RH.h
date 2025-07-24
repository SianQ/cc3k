#include "Potion.h"
#include "Character.h"

class RestoreHealthPotion : public Potion {
    public:
        void use(Character& target) override {
            int healed = std::min(10, target.getMaxHP() - target.getHP());
            target.setHP(target.getHP() + healed);
        }
        PotionType getType() const override { return PotionType::RH; }
    };
    
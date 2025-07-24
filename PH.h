#include "Potion.h"
#include "Character.h"

class PotionHealth : public Potion {
    public:
        void use(Character& target) override {
            int damaged = std::min(10, target.getHP());
            target.setHP(target.getHP() - damaged);
        }
        PotionType getType() const override { return PotionType::PH; }
    };
#include "Potion.h"

class RestoreHealthPotion : public Potion {
    public:
        void use(Character& target) override {
            int healed = std::min(10, target->getMaxHP() - target->getHP());
            target->setHP(target->getHP() + healed);
        }
        std::string getType() const override { return "RH"; }
    };
    
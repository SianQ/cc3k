#include "RH.h"

void RestoreHealthPotion::use(Character& target) {
    int healed = 0;
    if (target.getRace() == "V") {
        healed = 10;
    } else {
        healed = std::min(10, target.getMaxHP() - target.getHP());
    }
    target.setHP(target.getHP() + healed);
}

PotionType RestoreHealthPotion::getType() const {
    return PotionType::RH; 
}

std::string RestoreHealthPotion::getName() const {
    return "RH";
} 

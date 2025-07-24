#include "RH.h"

void RestoreHealthPotion::use(Character& target) {
    int healed = std::min(10, target.getMaxHP() - target.getHP());
    target.setHP(target.getHP() + healed);
}

PotionType RestoreHealthPotion::getType() const {
    return PotionType::RH; 
}
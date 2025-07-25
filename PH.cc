#include "PH.h"

void PotionHealth::use(Character& target) {
    int damaged = std::min(10, target.getHP());
    target.setHP(target.getHP() - damaged);
}

PotionType PotionHealth::getType() const {
    return PotionType::PH; 
}

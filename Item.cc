#include "Item.h"

Item::~Item() = default;

PotionType Item::getType() const {
    return PotionType::WD;
}

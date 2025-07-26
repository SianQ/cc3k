module Item;

Item::~Item() = default;

PotionType Item::getType() const {
    return PotionType::WD;
}

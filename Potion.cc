#include "Potion.h"

void Potion::use(Character& consumer) {
    std::string type = this->getType();

    // Apply permanent HP effect directly
    if (type == "RH" || type == "PH") {
        this->use(consumer);
    } else {
        // Apply decorators for temporary effects
        if (type == "BA") {
            consumer = std::make_shared<BoostAtkDecorator>(consumer, 5);
        } else if (type == "BD") {
            consumer = std::make_shared<BoostDefDecorator>(consumer, 5);
        } else if (type == "WA") {
            consumer = std::make_shared<WoundAtkDecorator>(consumer, 5);
        } else if (type == "WD") {
            consumer = std::make_shared<WoundDefDecorator>(consumer, 5);
        }
    }
}
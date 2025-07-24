#include "Gold.h"

Gold::Gold(int value, bool guarded) : value{value}, guardedByDragon{guarded} {}

void Gold::use(Character &consumer) {
    if (!guardedByDragon) {
        consumer.addGold(value);
    }
}

#include "Gold.h"
#include "Character.h"

Gold::Gold(int value, bool guarded)
    : Item(), value(value), guardedByDragon(guarded)
{
}

void Gold::use(Character &consumer)
{
    if (!guardedByDragon) {
        consumer.addGold(value);
    }
}

std::string Gold::getName() const
{
    return "Gold (" + std::to_string(value) + ")";
}

bool Gold::isGold()
{
    return true;
}

bool Gold::isPotion()
{
    return false;
}

bool Gold::isStair()
{
    return false;
}

int Gold::getValue() const
{
    return value;
}

bool Gold::isGuarded() const
{
    return guardedByDragon;
}

#include "Gold.h"
#include "Character.h"

Gold::Gold(int value, bool guarded)
    : Item(), value(value), guardedByDragon(guarded)
{
}

void Gold::use(Character &consumer)
{
    // Implementation depends on how Character handles gold
    // This may need to be implemented based on your Character class
}

char Gold::getSymbol() const
{
    return 'G';
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

void Gold::changeGuarded()
{
    guardedByDragon = !guardedByDragon;
}
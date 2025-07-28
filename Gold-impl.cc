module Gold;

Gold::Gold(int value, bool guarded)
    : Item(), value(value), guardedByDragon(guarded) {}

char Gold::getSymbol() const
{
    return 'G';
}

bool Gold::isGold()
{
    return true;
}


int Gold::getValue() const
{
    return value;
}

bool Gold::isGuarded() const
{
    return guardedByDragon;
}

void Gold::setGuarded(bool guarded)
{
    guardedByDragon = guarded;
}

module Dragon;

import Race;
import Enemy;

Dragon::Dragon()
    : Enemy(Race::Dragon, 150, 20, 20) {}

void Dragon::setHoard(int x, int y) {
    hoardX = x;
    hoardY = y;
}

int Dragon::getHoardX() {
    return hoardX;
}

int Dragon::getHoardY() {
    return hoardY;
}

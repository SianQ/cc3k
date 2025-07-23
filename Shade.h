#ifndef SHADE_H
#define SHADE_H

#include "Player.h"  // ✅ this is fine as long as Player.h doesn't include Troll.h

class Shade : public Player {
public:
    Shade();
    ~Shade() override;
};

#endif

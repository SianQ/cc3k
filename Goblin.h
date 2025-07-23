#ifndef GOBLIN_H
#define GOBLIN_H

#include "Player.h"  // ✅ this is fine as long as Player.h doesn't include Troll.h

class Goblin : public Player {
public:
    Goblin();
    ~Goblin() override;
};

#endif

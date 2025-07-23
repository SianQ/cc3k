#ifndef TROLL_H
#define TROLL_H

#include "Player.h"  // ✅ this is fine as long as Player.h doesn't include Troll.h

class Troll : public Player {
public:
    Troll();
    ~Troll() override;
};

#endif

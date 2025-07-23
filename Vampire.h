#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "Player.h"  // ✅ this is fine as long as Player.h doesn't include Troll.h

class Vampire : public Player {
public:
    Vampire();
    ~Vampire() override;
};

#endif

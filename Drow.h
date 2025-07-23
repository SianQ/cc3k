#ifndef DROW_H
#define DROW_H

#include "Player.h"  // ✅ this is fine as long as Player.h doesn't include Troll.h

class Drow : public Player {
public:
    Drow();
    ~Drow() override;
};

#endif

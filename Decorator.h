#include "Character.h"
#include "Player.h"
#include <memory.h>
#include <memory>

class Decorator: public Player {
protected:
    std::shared_ptr<Player> next;
public:
    Decorator(std::shared_ptr<Player> next);
    
};

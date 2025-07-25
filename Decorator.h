#include "Character.h"

class Decorator: public Character {
protected:
    Character *next;
public:
    Decorator(Character* next);
    virtual ~Decorator();
};

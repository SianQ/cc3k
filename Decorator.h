#include "Character.h"
#include <memory>
#include <algorithm>

class CharacterDecorator : public Character {
protected:
    std::shared_ptr<Character> base;

public:
    CharacterDecorator(std::shared_ptr<Character> base);
    virtual ~CharacterDecorator() = default;

    virtual int getAtk() const;
    virtual int getDef() const;
    virtual int getHP() const;

};

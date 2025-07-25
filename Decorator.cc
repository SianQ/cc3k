#include "Decorator.h"
#include "Character.h"

Decorator::Decorator(Character* next): next{next} {}

Decorator::~Decorator() {delete next;}

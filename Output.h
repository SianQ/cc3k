// export module Output;

// import Level;

// export

#pragma once
#include "Level.h"

class Output{
public:
    void displayMenu();
    void render(const Level& level);
    void renderGameOver();
    void clearScreen();
};

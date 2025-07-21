// export module Cc3k;

// import level;

// export 

#pragma once
#include "Input.h"
#include "Level.h"
#include "Output.h"

class Cc3k {
private:
    Level level;
    Input input;
    Output output;
    bool isRunning;

public:
    Cc3k();
    void run();
};

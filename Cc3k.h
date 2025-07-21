// export module Cc3k;

// import level;
// import input;
// import output;

// export 

#include "Level.h"
#include "Input.h"
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

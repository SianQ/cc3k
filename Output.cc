// module Output;

#include "Output.h"
#include <iostream>
#include <string>

using namespace std;

void Output::clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}

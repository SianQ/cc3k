// module Cc3k;

#include "Cc3k.h"
#include "Level.h"

Cc3k::Cc3k(std::string mapPath):
    level(mapPath),
    input(),
    output(),
    isRunning(true) 
{}

void Cc3k::run() {
    using namespace std;

    // Display start screen
    cout << "CC3K" << endl;
    cout << "> Press Enter to Start <" << endl;
    string temp;
    getline(cin, temp);
    output.clearScreen();

    // Display choose race screen
    cout << "Choose Player Race:" << endl;
    
}

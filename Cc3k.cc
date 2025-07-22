// module Cc3k;

#include "Cc3k.h"
#include "Character.h"
#include "Level.h"

using namespace std;

Cc3k::Cc3k(std::string mapPath):
    level(mapPath),
    input(),
    output(),
    isRunning(true) 
{}

void displayStartScreen() {
    cout << "CC3K" << endl;
    cout << "> Press Enter to Start <" << endl;
    string temp;
    getline(cin, temp);
}

void Cc3k::run() {
    displayStartScreen();
    output.clearScreen();

    cout << "Choose Player Race:" << endl;
    for (size_t i = 0; i < Player::RaceNames.size(); ++i) {
        cout << i + 1 << ". " << Player::RaceNames[i] << endl;
    }
    cout << "> ";
    size_t choice = 1;
    cin >> choice;
    if (choice >= 1 && choice <= Player::RaceNames.size())
}

// module Cc3k;

#include "Cc3k.h"
#include "Character.h"
#include "Level.h"

using namespace std;

Cc3k::Cc3k(std::string mapPath, int seed):
    level(mapPath, seed),
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

string chooseRace() {
    cout << "Choose Player Race:" << endl;
    for (size_t i = 0; i < Player::RaceNames.size(); ++i) {
        cout << Player::RaceNames[i].substr(0, 1) << ": " << Player::RaceNames[i] << endl;
    }
    cout << "> ";
    size_t choice = 1;
    cin >> choice;
    if (choice < 1 || choice > Player::RaceNames.size()) {
        return chooseRace();
    }
    cout << "Your race is: " << Player::RaceNames[choice] << endl;
    return Player::RaceNames[choice];
}

void Cc3k::run() {
    displayStartScreen();
    output.clearScreen();

    string playerRace = chooseRace();
    output.clearScreen();
    level.setPlayer(Player::create(playerRace));

    output.render(level);

    while(!level.isGameOver()) {
        input.applyInput(level);
        output.render(level);

        level.updateEnemies();
        output.render(level);
    }
}

bool Cc3k::isEnded() {
    if (levelNum == 5 || level.getPlayer().getHP() <= 0) {
        return true;
    }
    return false;
}

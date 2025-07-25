// module Cc3k;

#pragma once
#include "Cc3k.h"
#include "Level.h"

using namespace std;

Cc3k::Cc3k(std::string mapPath, int seed):
    level(mapPath, seed),
    input(),
    output(),
    masterRng(seed),
    mapPath(mapPath),
    isRunning(true)
{}

void displayStartScreen() {
    cout << "CC3K" << endl;
    cout << "> Press Enter to Start <" << endl;
    string temp;
    getline(cin, temp);
}

std::string chooseRace() {
    std::string line;
    while (true) {
        std::cout
            << "Choose your race (or q to quit):\n"
               "  (s)hade   (d)row   (v)ampire   (g)oblin   (t)roll   (q)uit\n"
               "Enter s, d, v, g, t, or q: ";
        if (!std::getline(std::cin, line)) {
            // EOF or error: exit
            std::exit(0);
        }
        if (line.empty()) {
            std::cout << "No input given. Please try again.\n";
            continue;
        }
        char c = std::tolower(line[0]);
        switch (c) {
            case 's': return "s";
            case 'd': return "d";
            case 'v': return "v";
            case 'g': return "g";
            case 't': return "t";
            case 'q': std::exit(0);
            default:
                std::cout 
                    << "Invalid choice '" << line[0] 
                    << "'. Please enter s, d, v, g, t, or q.\n";
        }
    }
}

void Cc3k::run() {
    displayStartScreen();
    output.clearScreen();

    string playerRace = chooseRace();
    output.clearScreen();
    level.spawnPlayer(playerRace);

    output.render(level);

    while(!level.isGameOver()) {
        input.applyInput(level);
        output.render(level);

        level.updateEnemies();
        output.render(level);

        if (level.isFinished) {
            unsigned nextSeed = masterRng();
            level = Level(mapPath, nextSeed);
            level.spawnPlayer(playerRace);
            output.render(level);       
        }
    }
}

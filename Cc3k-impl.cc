module Cc3k;
import Level;
import Output;
import Race;
using namespace std;

Cc3k::Cc3k(string mapPath, int seed):
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

string chooseRace() {
    string line;
    while (true) {
        cout
            << "Choose your race (or q to quit):\n"
               "  (s)hade   (d)row   (v)ampire   (g)oblin   (t)roll   (q)uit\n"
               "Enter s, d, v, g, t, or q: ";
        if (!getline(cin, line)) {
            // EOF or error: exit
            exit(0);
        }
        if (line.empty()) {
            cout << "No input given. Please try again.\n";
            continue;
        }
        char c = tolower(line[0]);
        switch (c) {
            case 's': return Race::Shade;
            case 'd': return Race::Drow;
            case 'v': return Race::Vampire;
            case 'g': return Race::Goblin;
            case 't': return Race::Troll;
            case 'q': exit(0);
            default:
                cout 
                    << "Invalid choice '" << line[0] 
                    << "'. Please enter s, d, v, g, t, or q.\n";
        }
    }
}

bool displayGameOver(bool isWin) {
    string input;
    if (isWin) cout << "====== YOU WIN ======\n";
    else       cout << "===== GAME OVER =====\n";
    cout << "Would you like to restart or quit? (r/q): ";
    
    while (true) {
        getline(cin, input);
        if (input == "r" || input == "R") {
            return true;
        } else if (input == "q" || input == "Q") {
            return false;
        } else {
            cout << "Invalid input. Enter 'r' to restart or 'q' to quit: ";
        }
    }
}


void Cc3k::run() {
    while (true) {
        displayStartScreen();

        string playerRace = chooseRace();
        level.spawnPlayer(playerRace);
        output.render(level);

        while (true) {
            level.perTermEvent();
            input.applyInput(level);
            level.updateEnemies();
            output.render(level);

            if (level.isFinished()) {
                unsigned nextSeed = masterRng();
                level = Level(mapPath, nextSeed);
                level.spawnPlayer(playerRace);
                output.render(level);       
            }

            if (level.isGameOver()) {
                if (!displayGameOver(false)) exit(0);
                break;
            }

            if (level.isGameComplete()) {
                if (!displayGameOver(true)) exit(0);
                break;
            }

            level.clearLog();
        }
    }
}

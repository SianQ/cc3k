module Cc3k;
import <iostream>;

using namespace std;

Cc3k::Cc3k(string mapPath, int seed) 
    : level(mapPath, seed, 1), masterRng(seed), mapPath(mapPath), isRunning(true) {}

void Cc3k::run() {
    cout << "Welcome to CC3K!" << endl;
    
    while (isRunning) {
        output.render(level);
        level.clearMessages();
        
        input.applyInput(level);
        level.updateEnemies();
        
        // 检查游戏结束条件
        if (level.getPlayer().isDead()) {
            output.renderGameOver();
            cout << "You have been slain!" << endl;
            isRunning = false;
        } else if (level.isGameComplete()) {
            output.renderGameOver();
            cout << "Congratulations! You won!" << endl;
            isRunning = false;
        }
    }
}

// EnemyUpdater.cpp

#include "Level.h"
#include "Enemy.h"
#include "Map.h"
#include "Player.h"

/// Drive the entire enemy phase.
/// Clears the previous log, then for each live enemy:
///   • call act(map,*player)
///   • if the player died, set gameOver, append a message, and stop.
void Level::updateEnemies() {
    // Start fresh for this enemy turn
    clearLog();

    // Loop in spawn order
    for (auto& up : enemyStore) {
        Enemy* e = up.get();
        if (!e) continue;
        if (e->isDead()) continue; 

        // Let this enemy act (move or attack)
        e->act(map, *player);

        // If the PC died during that action, end the game
        if (player->isDead()) {
            gameOver = true;
            appendMessage("Player has been slain.");
            break;
        }
    }
}

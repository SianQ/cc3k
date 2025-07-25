// EnemyUpdater.cc
#include "EnemyUpdater.h"
#include "Level.h"
#include "Enemy.h"
#include "Player.h"

/// Drive the entire enemy phase.
/// Clears the previous log, then for each live enemy:
///   • call act(map,*player)
void Level::updateEnemies() {
    // Loop through all enemies, let them act (dead enemies will handle cleanup once)
    for (auto& enemyPtr : enemyStore) {
        // Check if the unique_ptr is valid
        if (!enemyPtr) {
            continue;
        }
        
        Enemy* e = enemyPtr.get();
        if (!e) {
            continue;
        }
        
        // Let this enemy act (it will handle its own death cleanup if needed)
        e->act(map, *player, *this);

        // If the PC died during that action, end the game
        if (player->isDead()) {
            appendMessage("Player has been slain.");
            break;
        }
    }
}

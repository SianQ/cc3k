// EnemyUpdater.cc
#include "EnemyUpdater.h"
#include "Level.h"
#include "Enemy.h"
#include "Player.h"

/// Drive the entire enemy phase.
/// Clears the previous log, then for each live enemy:
///   • call act(map,*player)
void Level::updateEnemies() {
    // Loop in spawn order, removing dead enemies after they clean up
    for (auto it = enemyStore.begin(); it != enemyStore.end(); ) {
        // Check if the unique_ptr is valid
        if (!(*it)) {
            it = enemyStore.erase(it);
            continue;
        }
        
        Enemy* e = it->get();
        if (!e) {
            it = enemyStore.erase(it);
            continue;
        }
        
        bool wasAlive = !e->isDead();
        
        // Let this enemy act (it will handle its own death cleanup if needed)
        e->act(map, *player, *this);

        // If the enemy just died, remove it from the store
        if (wasAlive && e->isDead()) {
            it = enemyStore.erase(it);
        } else if (!wasAlive) {
            // Enemy was already dead, remove it without calling act again
            it = enemyStore.erase(it);
        } else {
            ++it;
        }

        // If the PC died during that action, end the game
        if (player->isDead()) {
            appendMessage("Player has been slain.");
            break;
        }
    }
}

export module EnemyUpdater;
import Level;

/**
 *  Collects and runs all of the enemy‐turn logic in one place,
 *  so that Level.cc doesn’t have to change.
 */
namespace EnemyUpdater {
  /**
   *  Drive one full “enemy” phase:
   *   - for each alive Enemy in level.enemies
   *     • call act(map, *player)
   *     • append any messages/log entries
   *     • stop early if the player died
   */
  void updateEnemies(Level& level);
}

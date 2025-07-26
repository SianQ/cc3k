export module Halfling;
import Enemy;

/**
 * Halfling: HP=100, Atk=15, Def=20.
 * When attacked by player, 50% chance to evade.
 * Drops one pile of 2 gold.
 */
export class Halfling : public Enemy {
public:
    Halfling();
};

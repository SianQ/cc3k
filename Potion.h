// Potion.h
#pragma once

#include <string>
#include "Item.h"

// Forward declaration
class Character;

/**
 * Enumeration of potion types
 */
enum class PotionType { RH, BA, BD, PH, WA, WD };

/**
 * Potion: applying use() applies an effect to the consumer
 * and marks the potion as discovered.
 */
class Potion : public Item {
public:
    Potion(PotionType t);

    // Apply the potion effect to the consumer and mark discovered = true
    void use(Character &consumer) override;

    // If discovered, returns the specific name (e.g. "Restore Health Potion"),
    // otherwise returns "Unknown Potion"
    std::string getName() const override;

    PotionType getType() const;
    bool       isDiscovered() const;
    void       markDiscovered();

    // Returns true for temporary effects (BA/BD/WA/WD), false for permanent (RH/PH)
    bool isTemporary() const;

private:
    PotionType type;
    bool       discovered = false;
};

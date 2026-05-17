// ============================================================================
// Dealer.h
// Purpose: Defines the Dealer class, which inherits from Player
// Description: Represents the dealer in a blackjack game with dealer-specific rules
// ============================================================================

#pragma once
#include "Player.h"
using namespace std;

// Dealer class - Inherits from Player
// Represents the dealer with specific blackjack rules:
// - Must hit on 16 or less
// - Must stand on 17 or more
class Dealer : public Player {
public:
    // Constructor - Creates a dealer with name "Dealer"
    Dealer();
    // Virtual Destructor - Ensures proper cleanup of the Dealer object
    ~Dealer() override;

    // wantsToHit() - Override of Player's method
    // Implements dealer rules: returns true if hand value is less than 17
    bool wantsToHit() const override;
    // showHand() - Override of Player's method
    // Displays hand with "Dealer's" prefix instead of generic player name
    void showHand(bool hideFirstCard = false) const override;
};


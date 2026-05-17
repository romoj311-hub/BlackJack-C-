// ============================================================================
// Dealer.cpp
// Implementation of the Dealer class with dealer-specific blackjack rules
// ============================================================================

#include "Dealer.h"
#include <iostream>
using namespace std;

// Constructor - Creates a dealer with the name "Dealer"
// Calls the parent Player constructor with "Dealer" as the name
Dealer::Dealer()
    : Player("Dealer") {
}

// Virtual Destructor - Cleans up the dealer object
Dealer::~Dealer() {
}

// wantsToHit() - Implements standard blackjack dealer rules
// Dealer must hit on 16 or less, must stand on 17 or more
// Returns: true if hand value is less than 17 (must hit)
bool Dealer::wantsToHit() const {
    return getHandValue() < 17;
}

// showHand() - Override of Player's showHand method
// Displays the dealer's hand with "Dealer's" prefix
// Calls the parent Player::showHand() method with the hideFirstCard parameter
// Parameters: hideFirstCard - if true, hides the dealer's hole card
void Dealer::showHand(bool hideFirstCard) const {
    cout << "Dealer's ";
    // Call parent class showHand() method
    Player::showHand(hideFirstCard);
}

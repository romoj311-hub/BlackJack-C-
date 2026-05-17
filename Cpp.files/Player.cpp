// ============================================================================
// Player.cpp
// Implementation of the Player class for the blackjack game
// ============================================================================

#include "Player.h"
#include <iostream>
using namespace std;

// Constructor - Creates a player with the specified name
// Parameters: name - the player's name (default: "Player")
Player::Player(const string& name)
    : name(name) {
}

// Virtual Destructor - Cleans up the player object
Player::~Player() {
}

// clearHand() - Removes all cards from the player's hand
// Used when starting a new game round
void Player::clearHand() {
    hand.clear();
}

// addCard() - Adds a card value to the player's hand
// Parameters: value - the blackjack value of the card (typically 2-11)
void Player::addCard(int value) {
    hand.push_back(value);
}

// getHandValue() - Calculates the total value of all cards in the player's hand
// Handles Ace logic: Aces can be worth 11 or 1 to avoid busting if possible
// Returns: the optimal hand value (highest value without exceeding 21)
int Player::getHandValue() const {
    int total = 0;
    int aceCount = 0;

    // Sum all card values and count the number of Aces (value 11)
    for (int value : hand) {
        total += value;
        if (value == 11) {
            aceCount++;
        }
    }

    // If the total exceeds 21 and we have Aces, convert them from 11 to 1
    // (effectively subtracting 10 from the total for each Ace converted)
    while (total > 21 && aceCount > 0) {
        total -= 10;  // Convert an Ace from 11 to 1
        aceCount--;   // One less Ace to convert
    }

    return total;
}

// getName() - Getter method that returns the player's name
const string& Player::getName() const {
    return name;
}

// setName() - Setter method that changes the player's name
// Parameters: newName - the new name for the player
void Player::setName(const string& newName) {
    name = newName;
}

// wantsToHit() - Virtual method determining if the player wants to hit
// Base class returns false (player decision in main game loop)
// Overridden in Dealer class to implement dealer rules (hit on 16, stand on 17)
bool Player::wantsToHit() const {
    return false;
}

// showHand() - Virtual method that displays the player's hand and total value
// Parameters: hideFirstCard - if true, hides the value of the first card (dealer's hole card)
void Player::showHand(bool hideFirstCard) const {
    cout << name << "'s hand: ";

    // Display each card value, hiding the first if requested
    for (size_t i = 0; i < hand.size(); ++i) {
        if (hideFirstCard && i == 0) {
            cout << "[hidden] ";  // Hide first card (dealer's hole card)
        }
        else {
            cout << hand[i] << " ";  // Show card value
        }
    }

    // Show the hand total, hiding it if first card is hidden
    if (hideFirstCard) {
        cout << "(value hidden)" << endl;
    }
    else {
        cout << "(value = " << getHandValue() << ")" << endl;
    }
}

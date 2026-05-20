// ============================================================================
// Player.h
// Purpose: Defines the Player base class for blackjack game
// Description: Represents a player with a hand of cards and basic actions
//              This is a base class that Dealer inherits from
// ============================================================================

#pragma once
#include <string>
#include <vector>
using namespace std;

// The Player class represents a player in blackjack
// It manages the player's hand and provides methods to hit/stand
// The Dealer class inherits from this and overrides behavior for dealer rules
class Player {
protected:
    // Player's name (e.g., "Player", "Dealer")
    string name;
    // Vector of card values in the player's hand
    vector<int> hand;

public:
    // Constructor - Creates a player with the given name
    Player(const string& name = "Player");
    // Virtual destructor - allows proper cleanup of derived classes
    virtual ~Player();

    // clearHand() - Removes all cards from the player's hand
    void clearHand();
    // addCard() - Adds a card value to the player's hand
    // Parameters: value - the blackjack value of the card (1-11)
    void addCard(int value);
    // getHandValue() - Calculates and returns the total value of the player's hand
    // Handles Ace logic (can be 1 or 11) to avoid busting if possible
    int getHandValue() const;
    const vector<int>& getHand() const { return hand; } // for SFML rendering

    // getName() - Returns the player's name
    const string& getName() const;
    // setName() - Sets the player's name
    void setName(const string& newName);

    // wantsToHit() - Virtual method determining if player wants another card
    // Returns false for regular player (player decides), overridden for dealer
    virtual bool wantsToHit() const;
    // showHand() - Virtual method displaying the player's hand
    // Parameters: hideFirstCard - if true, hides the first card (used for dealer's hidden card)
    virtual void showHand(bool hideFirstCard = false) const;
};

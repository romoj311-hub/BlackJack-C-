// ============================================================================
// CardDeck.h
// Purpose: Defines the CardDeck class for managing a 52-card deck
// Description: Manages a standard deck of cards with shuffle, deal, and reset
// ============================================================================

#pragma once
#include "Card.h"
#include <vector>
using namespace std;

// CardDeck class manages a standard 52-card deck used in blackjack
// Features: initialization, shuffling, dealing, tracking remaining cards
class CardDeck {
private:
    // m_Cards - vector storing all cards in the deck
    vector<Card> m_Cards;

public:
    // Constructor - initializes and shuffles a new deck
    CardDeck();
    // Destructor
    ~CardDeck();

    // initialize() - Creates a fresh 52-card deck with all suits and ranks
    void initialize();
    // shuffle() - Randomly shuffles the current deck
    void shuffle();
    // dealCard() - Removes and returns the top card from the deck
    // Automatically reshuffles if the deck runs out
    Card dealCard();
    // cardsRemaining() - Returns the number of cards left in the deck
    int cardsRemaining() const;
    // isEmpty() - Returns true if the deck has no cards left
    bool isEmpty() const;
    // reset() - Clears the deck and creates a fresh shuffled deck
    void reset();
};

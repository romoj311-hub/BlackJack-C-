// ============================================================================
// CardDeck.cpp
// Implementation of the CardDeck class for managing a standard 52-card deck
// ============================================================================

#include "CardDeck.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

// Constructor - Creates a new deck and shuffles it
CardDeck::CardDeck() {
    initialize();
    shuffle();
}

// Destructor - Cleans up the deck
CardDeck::~CardDeck() {
}

// initialize() - Creates a fresh standard 52-card deck
// Generates all combinations of 4 suits and 13 ranks
void CardDeck::initialize() {
    m_Cards.clear();

    // Create all 52 cards (4 suits, 13 ranks each)
    Suit suits[] = { Suit::Hearts, Suit::Diamonds, Suit::Clubs, Suit::Spades };
    Rank ranks[] = { Rank::Ace, Rank::Two, Rank::Three, Rank::Four, Rank::Five,
                     Rank::Six, Rank::Seven, Rank::Eight, Rank::Nine, Rank::Ten,
                     Rank::Jack, Rank::Queen, Rank::King };

    // Generate each combination of suit and rank
    for (Suit suit : suits) {
        for (Rank rank : ranks) {
            m_Cards.push_back(Card(rank, suit));
        }
    }
}

// shuffle() - Randomly shuffles all cards in the deck using Mersenne Twister algorithm
void CardDeck::shuffle() {
    // Use Mersenne Twister random number generator seeded with current time
    static mt19937 rng(static_cast<unsigned>(time(0)));
    // Shuffle the card vector randomly
    std::shuffle(m_Cards.begin(), m_Cards.end(), rng);
}

// dealCard() - Removes and returns the top card from the deck
// If deck is empty, automatically reinitializes and reshuffles
Card CardDeck::dealCard() {
    if (isEmpty()) {
        cout << "Warning: Deck is empty! Reshuffling..." << endl;
        initialize();
        shuffle();
    }

    // Get the card from the back of the vector (top of the deck)
    Card card = m_Cards.back();
    // Remove the card from the deck
    m_Cards.pop_back();
    return card;
}

// cardsRemaining() - Returns the number of undealt cards in the deck
int CardDeck::cardsRemaining() const {
    return m_Cards.size();
}

// isEmpty() - Returns true if there are no cards left in the deck
bool CardDeck::isEmpty() const {
    return m_Cards.empty();
}

// reset() - Clears the deck and creates a fresh shuffled 52-card deck
// Used when starting a new game or when the deck is depleted
void CardDeck::reset() {
    initialize();
    shuffle();
}

// ============================================================================
// Card.h
// Purpose: Defines the Card class and enums for suit and rank
// Description: Represents a single playing card with rank, suit, and visibility
// ============================================================================

#pragma once
#include <iostream>
#include <string>
using namespace std;

// Suit enum - represents the four card suits
enum class Suit {
	Hearts,      // Hearts suit
	Diamonds,    // Diamonds suit
	Clubs,       // Clubs suit
	Spades       // Spades suit
};

// Rank enum - represents the 13 card ranks in a standard deck
enum class Rank {
	Ace = 1,       
	Two = 2,       // Two
	Three = 3,     // Three
	Four = 4,      // Four
	Five = 5,      // Five
	Six = 6,       // Six
	Seven = 7,     // Seven
	Eight = 8,     // Eight
	Nine = 9,      // Nine
	Ten = 10,      // Ten (worth 10 in blackjack)
	Jack = 11,     // Jack (worth 10 in blackjack)
	Queen = 12,    // Queen (worth 10 in blackjack)
	King = 13      // King (worth 10 in blackjack)
};

// Card class - represents a single playing card
class Card
{
private:
	Rank m_Rank;       // The rank of the card (Ace through King)
	Suit m_Suit;       // The suit of the card (Hearts, Diamonds, Clubs, Spades)
	bool m_IsFaceUp;   // Whether the card is visible (true) or hidden (false)

public:
	// Constructor and destructor
	Card(Rank rank = Rank::Ace, Suit suit = Suit::Hearts);
	~Card();

	// ===== Getter Methods =====
	// getValue() - Returns the blackjack value of the card (11 for Ace, 10 for face cards, etc.)
	int getValue() const;
	// getRank() - Returns the card's rank
	Rank getRank() const;
	// getSuit() - Returns the card's suit
	Suit getSuit() const;
	// isFaceUp() - Returns whether the card is visible
	bool isFaceUp() const;
	// getRankString() - Returns the rank as a readable string ("Ace", "2", "Jack", etc.)
	string getRankString() const;
	// getSuitString() - Returns the suit as a readable string ("Hearts", "Diamonds", etc.)
	string getSuitString() const;
	// getCardName() - Returns the full card name (e.g., "Ace of Hearts") or "[Hidden Card]" if face down
	string getCardName() const;

	// ===== Card Action Methods =====
	// flip() - Toggles the card's face-up state
	void flip();
	// setFaceUp() - Sets the card's face-up state to the specified value
	void setFaceUp(bool faceUp);
};

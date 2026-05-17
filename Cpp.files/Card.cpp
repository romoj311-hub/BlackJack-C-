// ============================================================================
// Card.cpp
// Implementation of the Card class methods
// ============================================================================

#include "Card.h"

// Constructor - Initializes a card with the given rank and suit
// Parameters: rank (default Ace), suit (default Hearts)
Card::Card(Rank rank, Suit suit)
    : m_Rank(rank), m_Suit(suit), m_IsFaceUp(true) {
}

// Destructor - Cleans up the card object
Card::~Card() {
}

// getValue() - Returns the blackjack value of the card
// Face cards (Jack, Queen, King) are worth 10 points
// Aces are worth 11 (the hand logic will adjust to 1 if needed to avoid busting)
// Number cards (2-10) are worth their face value
int Card::getValue() const {
    // Face cards (Jack, Queen, King) are worth 10
    // Aces are worth 11 (will be handled by hand logic to adjust to 1 if needed)
    if (m_Rank == Rank::Jack || m_Rank == Rank::Queen || m_Rank == Rank::King) {
        return 10;
    }
    else if (m_Rank == Rank::Ace) {
        return 11;
    }
    else {
        return static_cast<int>(m_Rank);
    }
}

// getRank() - Getter method that returns the card's rank
Rank Card::getRank() const {
    return m_Rank;
}

// getSuit() - Getter method that returns the card's suit
Suit Card::getSuit() const {
    return m_Suit;
}

// isFaceUp() - Getter method that returns whether the card is face-up (visible)
bool Card::isFaceUp() const {
    return m_IsFaceUp;
}

// getRankString() - Converts the card's rank to a readable string
// Returns: "Ace", "2", "3", ..., "10", "Jack", "Queen", "King"
string Card::getRankString() const {
    switch (m_Rank) {
        case Rank::Ace:
            return "Ace";
        case Rank::Two:
            return "2";
        case Rank::Three:
            return "3";
        case Rank::Four:
            return "4";
        case Rank::Five:
            return "5";
        case Rank::Six:
            return "6";
        case Rank::Seven:
            return "7";
        case Rank::Eight:
            return "8";
        case Rank::Nine:
            return "9";
        case Rank::Ten:
            return "10";
        case Rank::Jack:
            return "Jack";
        case Rank::Queen:
            return "Queen";
        case Rank::King:
            return "King";
        default:
            return "Unknown";
    }
}

// getSuitString() - Converts the card's suit to a readable string
// Returns: "Hearts", "Diamonds", "Clubs", or "Spades"
string Card::getSuitString() const {
    switch (m_Suit) {
        case Suit::Hearts:
            return "Hearts";
        case Suit::Diamonds:
            return "Diamonds";
        case Suit::Clubs:
            return "Clubs";
        case Suit::Spades:
            return "Spades";
        default:
            return "Unknown";
    }
}

// getCardName() - Returns the full card name as a string
// If the card is face-up: returns format like "Ace of Hearts"
// If the card is face-down: returns "[Hidden Card]"
string Card::getCardName() const {
    if (!m_IsFaceUp) {
        return "[Hidden Card]";
    }
    return getRankString() + " of " + getSuitString();
}

// flip() - Toggles the card between face-up and face-down state
void Card::flip() {
    m_IsFaceUp = !m_IsFaceUp;
}

// setFaceUp() - Sets the card's face-up state to the specified value
// Parameters: faceUp - true to show the card, false to hide it
void Card::setFaceUp(bool faceUp) {
    m_IsFaceUp = faceUp;
}
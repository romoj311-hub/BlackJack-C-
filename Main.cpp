// ============================================================================
// Main.cpp
// Title: Blackjack Game
// Description: A playable blackjack game for one player vs the dealer
// Author: Juan , Anthony
// Date: 5/10/26
// ============================================================================
// This program implements a complete blackjack game where the player plays
// against the dealer. The game follows standard blackjack rules with Ace
// handling and dealer stand/hit rules at 17.
// ============================================================================

#include <iostream>
#include <string>
#include "Player.h"
#include "Dealer.h"
#include "CardDeck.h"
#include "Card.h"
using namespace std;

// ============================================================================
// displayGameStatus() - Helper function to display current game state
// ============================================================================
// Parameters:
//   player - reference to the player object
//   dealer - reference to the dealer object
//   hideDealer - if true, hides the dealer's hole card (first card)
// Purpose: Displays both players' hands and values in a clear format
void displayGameStatus(Player& player, Dealer& dealer, bool hideDealer) {
    cout << "\n";
    dealer.showHand(hideDealer);
    player.showHand();
    cout << "\n";
}

// ============================================================================
// playBlackjack() - Main game logic for a single round of blackjack
// ============================================================================
// Returns: true if the player wins the round, false if the dealer wins
// Game Flow:
//   1. Deal initial cards to player and dealer (2 cards each)
//   2. Check for blackjack (instant win/loss)
//   3. Player's turn (hit or stand)
//   4. Dealer's turn (automatic based on rules)
//   5. Compare final values to determine winner
bool playBlackjack() {
    // Create and reset the deck for this round
    CardDeck deck;
    deck.reset();

    // Create player and dealer objects
    Player player("Player");
    Dealer dealer;

    // ========== INITIAL DEAL ==========
    // Deal two cards to each player
    cout << "Dealing cards...\n";
    player.addCard(deck.dealCard().getValue());
    dealer.addCard(deck.dealCard().getValue());
    player.addCard(deck.dealCard().getValue());
    dealer.addCard(deck.dealCard().getValue());

    cout << "Cards remaining in deck: " << deck.cardsRemaining() << endl;
    displayGameStatus(player, dealer, true);  // Hide dealer's hole card

    // ========== CHECK FOR BLACKJACK ==========
    // Check if either player has 21 (blackjack) on initial deal
    if (player.getHandValue() == 21) {
        cout << "BLACKJACK! You win!\n";
        displayGameStatus(player, dealer, false);
        return true;
    }

    if (dealer.getHandValue() == 21) {
        cout << "Dealer has blackjack. You lose!\n";
        displayGameStatus(player, dealer, false);
        return false;
    }

    // ========== PLAYER'S TURN ==========
    // Player can hit (request another card) or stand (keep current total)
    while (true) {
        // Display current hand value
        cout << "Your hand value: " << player.getHandValue() << endl;
        // Prompt player for action
        cout << "Do you want to (H)it or (S)tand? ";

        string choice;
        cin >> choice;

        if (choice == "H" || choice == "h") {
            // Player hits - deal a new card
            Card newCard = deck.dealCard();
            player.addCard(newCard.getValue());
            cout << "\nYou drew: " << newCard.getCardName() << endl;
            cout << "Cards remaining in deck: " << deck.cardsRemaining() << endl;
            displayGameStatus(player, dealer, true);

            // Check if player busted (exceeded 21)
            if (player.getHandValue() > 21) {
                cout << "BUST! You went over 21. You lose!\n";
                displayGameStatus(player, dealer, false);
                return false;
            }
        }
        else if (choice == "S" || choice == "s") {
            // Player stands - end their turn
            cout << "\nYou stand with " << player.getHandValue() << ".\n";
            break;
        }
        else {
            // Invalid input - ask again
            cout << "Invalid input. Please enter H or S.\n";
        }
    }

    // ========== DEALER'S TURN ==========
    // Dealer's turn - dealer follows standard rules (hit on 16 or less, stand on 17+)
    cout << "\nDealer's turn...\n";
    displayGameStatus(player, dealer, false);  // Now reveal dealer's hole card

    // Dealer must hit while hand value is less than 17
    while (dealer.getHandValue() < 17) {
        Card newCard = deck.dealCard();
        dealer.addCard(newCard.getValue());
        cout << "Dealer draws: " << newCard.getCardName() << endl;
        cout << "Cards remaining in deck: " << deck.cardsRemaining() << endl;
        displayGameStatus(player, dealer, false);
    }

    // Check if dealer busted
    if (dealer.getHandValue() > 21) {
        cout << "Dealer busts! You win!\n";
        return true;
    }

    // ========== COMPARE FINAL HANDS ==========
    // Determine winner by comparing final hand values
    cout << "\nFinal Results:\n";
    cout << "Your hand value: " << player.getHandValue() << endl;
    cout << "Dealer's hand value: " << dealer.getHandValue() << endl;

    // Player wins if their hand is higher than dealer's
    if (player.getHandValue() > dealer.getHandValue()) {
        cout << "You win!\n";
        return true;
    }
    // Dealer wins if their hand is higher than player's
    else if (player.getHandValue() < dealer.getHandValue()) {
        cout << "Dealer wins! You lose!\n";
        return false;
    }
    // Push (tie) if hands are equal - dealer wins (convention)
    else {
        cout << "Push! It's a tie!\n";
        return false;
    }
}

// ============================================================================
// main() - Program entry point and game loop
// ============================================================================
// Orchestrates multiple rounds of blackjack and tracks overall score
int main()
{
    // Display welcome message
    cout << "========================================" << endl;
    cout << "       WELCOME TO BLACKJACK!" << endl;
    cout << "========================================" << endl;

    // Track cumulative wins across multiple rounds
    int playerWins = 0;
    int dealerWins = 0;

    // ========== MAIN GAME LOOP ==========
    // Play multiple rounds until player chooses to quit
    while (true) {
        // Play one round of blackjack
        bool playerWon = playBlackjack();

        // Update cumulative score
        if (playerWon) {
            playerWins++;
        }
        else {
            dealerWins++;
        }

        // Display current score
        cout << "\nScore - Player: " << playerWins << " | Dealer: " << dealerWins << endl;
        cout << "\nDo you want to play another hand? (Y/N): ";

        // Get player input for next round
        string playAgain;
        cin >> playAgain;

        // Exit loop if player chooses not to continue
        if (playAgain != "Y" && playAgain != "y") {
            break;
        }

        // Visual separator between rounds
        cout << "\n========================================\n";
    }

    // ========== GAME OVER ==========
    // Display final session statistics and exit
    cout << "\n========================================" << endl;
    cout << "          FINAL RESULTS" << endl;
    cout << "========================================" << endl;
    cout << "Your wins: " << playerWins << endl;
    cout << "Dealer wins: " << dealerWins << endl;
    cout << "Thanks for playing!" << endl;

    return 0;
}
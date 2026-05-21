/*
Title: Blackjack Game
Description: A playable blackjack game for one player vs the dealer
Author: Juan Romo-Torres
Date: 5/10/26
*/

#include <iostream>
#include <string>
#include "Player.h"
#include "Dealer.h"
#include "CardDeck.h"
#include "Card.h"
#include "Money.h"
using namespace std;

void displayGameStatus(Player& player, Dealer& dealer, bool hideDealer) {
    cout << "\n";
    dealer.showHand(hideDealer);
    player.showHand();
    cout << "\n";
}

bool playBlackjack(Money& playerMoney) {
    // Check if player has money to bet
    if (playerMoney.getBalance() <= 0) {
        cout << "Game Over! You're out of money!" << endl;
        return false;
    }

    CardDeck deck;
    deck.reset();

    Player player("Player");
    Dealer dealer;

    // Get bet from player
    cout << "\n========== NEW HAND ==========" << endl;
    playerMoney.displayBalance();
    cout << "Enter your bet: $";

    double betAmount;
    cin >> betAmount;

    // Validate and place bet
    while (!playerMoney.placeBet(betAmount)) {
        cout << "Enter your bet: $";
        cin >> betAmount;
    }

    playerMoney.displayBalance();

    // Deal initial two cards to each player
    cout << "\nDealing cards...\n";
    player.addCard(deck.dealCard().getValue());
    dealer.addCard(deck.dealCard().getValue());
    player.addCard(deck.dealCard().getValue());
    dealer.addCard(deck.dealCard().getValue());

    cout << "Cards remaining in deck: " << deck.cardsRemaining() << endl;
    displayGameStatus(player, dealer, true);

    // Check for blackjack
    if (player.getHandValue() == 21) {
        cout << "BLACKJACK! You win!\n";
        displayGameStatus(player, dealer, false);
        playerMoney.winBet();
        playerMoney.displayBalance();
        return true;
    }

    if (dealer.getHandValue() == 21) {
        cout << "Dealer has blackjack. You lose!\n";
        displayGameStatus(player, dealer, false);
        playerMoney.loseBet();
        playerMoney.displayBalance();
        return false;
    }

    // Player's turn
    while (true) {
        cout << "Your hand value: " << player.getHandValue() << endl;
        cout << "Do you want to (H)it or (S)tand? ";

        string choice;
        cin >> choice;

        if (choice == "H" || choice == "h") {
            Card newCard = deck.dealCard();
            player.addCard(newCard.getValue());
            cout << "\nYou drew: " << newCard.getCardName() << endl;
            cout << "Cards remaining in deck: " << deck.cardsRemaining() << endl;
            displayGameStatus(player, dealer, true);

            if (player.getHandValue() > 21) {
                cout << "BUST! You went over 21. You lose!\n";
                displayGameStatus(player, dealer, false);
                playerMoney.loseBet();
                playerMoney.displayBalance();
                return false;
            }
        }
        else if (choice == "S" || choice == "s") {
            cout << "\nYou stand with " << player.getHandValue() << ".\n";
            break;
        }
        else {
            cout << "Invalid input. Please enter H or S.\n";

        }
    }

    // Dealer's turn
    cout << "\nDealer's turn...\n";
    displayGameStatus(player, dealer, false);

    while (dealer.getHandValue() < 17) {
        Card newCard = deck.dealCard();
        dealer.addCard(newCard.getValue());
        cout << "Dealer draws: " << newCard.getCardName() << endl;
        cout << "Cards remaining in deck: " << deck.cardsRemaining() << endl;
        displayGameStatus(player, dealer, false);
    }

    if (dealer.getHandValue() > 21) {
        cout << "Dealer busts! You win!\n";
        playerMoney.winBet();
        playerMoney.displayBalance();
        return true;
    }

    // Determine winner
    cout << "\nFinal Results:\n";
    cout << "Your hand value: " << player.getHandValue() << endl;
    cout << "Dealer's hand value: " << dealer.getHandValue() << endl;

    if (player.getHandValue() > dealer.getHandValue()) {
        cout << "You win!\n";
        playerMoney.winBet();
        playerMoney.displayBalance();
        return true;
    }
    else if (player.getHandValue() < dealer.getHandValue()) {
        cout << "Dealer wins! You lose!\n";
        playerMoney.loseBet();
        playerMoney.displayBalance();
        return false;
    }
    else {
        cout << "Push! It's a tie! Your bet is returned.\n";
        playerMoney.addMoney(playerMoney.getCurrentBet());
        playerMoney.resetBet();
        playerMoney.displayBalance();
        return false;
    }
}

int main()
{
    cout << "========================================" << endl;
    cout << "       WELCOME TO BLACKJACK!" << endl;
    cout << "========================================" << endl;

    // Initialize player's money
    cout << "Enter your starting bankroll: $";
    double startingMoney;
    cin >> startingMoney;

    Money playerMoney(startingMoney);

    cout << "\nYou are starting with: ";
    playerMoney.displayBalance();

    int playerWins = 0;
    int dealerWins = 0;

    while (playerMoney.getBalance() > 0) {
        bool playerWon = playBlackjack(playerMoney);

        if (playerWon) {
            playerWins++;
        }
        else {
            dealerWins++;
        }

        // Check if player is out of money
        if (playerMoney.getBalance() <= 0) {
            cout << "\n========================================" << endl;
            cout << "GAME OVER - YOU'RE OUT OF MONEY!" << endl;
            cout << "========================================" << endl;
            break;
        }

        cout << "\nDo you want to play another hand? (Y/N): ";

        string playAgain;
        cin >> playAgain;

        if (playAgain != "Y" && playAgain != "y") {
            break;
        }

        cout << "\n========================================\n";
    }

    cout << "\n========================================" << endl;
    cout << "          FINAL RESULTS" << endl;
    cout << "========================================" << endl;
    cout << "Your wins: " << playerWins << endl;
    cout << "Dealer wins: " << dealerWins << endl;
    cout << "Final Balance: $";
    playerMoney.displayBalance();
    cout << "Thanks for playing!" << endl;

    return 0;
}
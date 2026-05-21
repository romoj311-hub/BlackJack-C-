#pragma once
#include <iostream>
using namespace std;

// Money class manages player betting and bankroll
class Money {
private:
    double m_Balance;
    double m_CurrentBet;

public:
    Money(double startingBalance = 100.0);
    ~Money();

    // Getters
    double getBalance() const;
    double getCurrentBet() const;

    // Betting functions
    bool placeBet(double amount);
    void winBet();
    void loseBet();
    void resetBet();

    // Balance management
    void addMoney(double amount);
    void subtractMoney(double amount);
    bool canAffordBet(double amount) const;

    // Display
    void displayBalance() const;
};

#include "Money.h"
#include <iomanip>

Money::Money(double startingBalance)
    : m_Balance(startingBalance), m_CurrentBet(0.0) {
    if (m_Balance < 0) {
        m_Balance = 0.0;
    }
}

Money::~Money() {
}

double Money::getBalance() const {
    return m_Balance;
}

double Money::getCurrentBet() const {
    return m_CurrentBet;
}

bool Money::placeBet(double amount) {
    // Validate bet
    if (amount <= 0) {
        cout << "Error: Bet must be greater than $0!" << endl;
        return false;
    }

    if (amount > m_Balance) {
        cout << "Error: You don't have enough money to place this bet!" << endl;
        cout << "Your balance: $" << fixed << setprecision(2) << m_Balance << endl;
        return false;
    }

    m_CurrentBet = amount;
    m_Balance -= amount;
    cout << "Bet placed: $" << fixed << setprecision(2) << m_CurrentBet << endl;
    return true;
}

void Money::winBet() {
    if (m_CurrentBet > 0) {
        // Return original bet plus winnings (double the bet)
        m_Balance += (m_CurrentBet * 2);
        cout << "You won! Your bet of $" << fixed << setprecision(2) << m_CurrentBet 
             << " has been doubled!" << endl;
        m_CurrentBet = 0.0;
    }
}

void Money::loseBet() {
    if (m_CurrentBet > 0) {
        cout << "You lost your bet of $" << fixed << setprecision(2) << m_CurrentBet << endl;
        m_CurrentBet = 0.0;
    }
}

void Money::resetBet() {
    m_CurrentBet = 0.0;
}

void Money::addMoney(double amount) {
    if (amount > 0) {
        m_Balance += amount;
    }
}

void Money::subtractMoney(double amount) {
    if (amount > 0 && amount <= m_Balance) {
        m_Balance -= amount;
    }
}

bool Money::canAffordBet(double amount) const {
    return (amount > 0 && amount <= m_Balance);
}

void Money::displayBalance() const {
    cout << "Balance: $" << fixed << setprecision(2) << m_Balance;
    if (m_CurrentBet > 0) {
        cout << " | Current Bet: $" << fixed << setprecision(2) << m_CurrentBet;
    }
    cout << endl;
}
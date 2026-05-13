#pragma once
#include <string>
#include <vector>
using namespace std;

// The Player class represents a general blackjack player, which can
// hit or stand and has a hand of cards. The Dealer class will inherit
// from this and implement specific behavior for the dealer.
// It stores a name and a hand of card values.
class Player {
protected:
    string name;
    vector<int> hand;

public:
    Player(const string& name = "Player");
    virtual ~Player();

    void clearHand();
    void addCard(int value);
    int getHandValue() const;

    const string& getName() const;
    void setName(const string& newName);

    virtual bool wantsToHit() const;
    virtual void showHand(bool hideFirstCard = false) const;
};

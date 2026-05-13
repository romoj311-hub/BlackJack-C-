#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(const string& name)
    : name(name) {
}

Player::~Player() {
}

void Player::clearHand() {
    hand.clear();
}

void Player::addCard(int value) {
    hand.push_back(value);
}

int Player::getHandValue() const {
    int total = 0;
    int aceCount = 0;

    for (int value : hand) {
        total += value;
        if (value == 11) {
            aceCount++;
        }
    }

    while (total > 21 && aceCount > 0) {
        total -= 10;
        aceCount--;
    }

    return total;
}

const string& Player::getName() const {
    return name;
}

void Player::setName(const string& newName) {
    name = newName;
}

bool Player::wantsToHit() const {
    return false;
}

void Player::showHand(bool hideFirstCard) const {
    cout << name << "'s hand: ";

    for (size_t i = 0; i < hand.size(); ++i) {
        if (hideFirstCard && i == 0) {
            cout << "[hidden] ";
        }
        else {
            cout << hand[i] << " ";
        }
    }

    if (hideFirstCard) {
        cout << "(value hidden)" << endl;
    }
    else {
        cout << "(value = " << getHandValue() << ")" << endl;
    }
}

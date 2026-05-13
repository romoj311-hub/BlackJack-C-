#include "Dealer.h"
#include <iostream>
using namespace std;

Dealer::Dealer()
    : Player("Dealer") {
}

Dealer::~Dealer() {
}

bool Dealer::wantsToHit() const {
    return getHandValue() < 17;
}

void Dealer::showHand(bool hideFirstCard) const {
    cout << "Dealer's ";
    Player::showHand(hideFirstCard);
}

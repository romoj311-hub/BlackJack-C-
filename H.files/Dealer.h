#pragma once
#include "Player.h"
using namespace std;

// Dealer is a special Player with its own hit/stand rules compared to the standard player.
class Dealer : public Player {
public:
    Dealer();
    ~Dealer() override;

    bool wantsToHit() const override;
    void showHand(bool hideFirstCard = false) const override;
};


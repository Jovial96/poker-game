#ifndef __Player__
#define __Player__

#include <vector>
#include <string>
#include "Card.h"

class Player {
private:
    std::vector<Card> hand;
    std::string name;
    int chips;
    bool folded;
    int currentBet;

public:
    Player(const std::string& name, int initialchips);

    void receiveCard(const Card& card);
    void showHand() const;
    void clearHand();

    bool hasFolded() const;
    void setHasFolded(bool folded);

    int getChips() const;
    void decreaseChips(int amount);

    int getCurrentBet() const;
    void setCurrentBet(int amount);

    const std::string& getName() const;
};

#endif
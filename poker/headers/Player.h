#pragma once    
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

    // void takeTurn(const GameState& state); placeholder
    void bet(int amount);
    void fold();
    void check();
    void call(int amount);
    void raise(int amount);

    int getChips();
    int getCurrentBet();
    bool isFolded();
public:
    Player(const std::string& name, int initialChips);
    void receiveCard(const Card& card);
    void showHand() const;
    void clearHand();
};
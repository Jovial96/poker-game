#pragma once    

#include "Deck.h"
#include "Player.h"
#include "Card.h"
#include <vector>
#include <iostream>

class PokerGame {
private:
    Deck deck;
    std::vector<Player> players;
    std::vector<Card> communityCards;
public:
    void addPlayer(const std::string& name);
    void startGame();
    void dealFlop();
    void dealTurn();
    void dealRiver();
    void showCommunityCards();
    void bettingRound();
    void showDown();
    void determineWinnter();
    
    friend std::ostream& operator<<(std::ostream& os, const std::vector<Card>& communityCards);
};
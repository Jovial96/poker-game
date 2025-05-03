#ifndef __GameManager__
#define __GameManager__

#include <vector>
#include "Player.h"
#include "Deck.h"
#include "Card.h"

class GameManagement {
private:
    std::vector<Player> players;
    std::vector<Card> communityCards;
    Deck deck;
    int currentPlayerIndex;
    bool gameOver;

public:
    GameManagement(std::vector<Player> players);

    void startNewRound();
    void dealCards();
    void dealCommunityCards(int numCards);
    void bettingRound();
    void evaluateHands();
    bool isGameOver() const;
    void playRound();
};

#endif
#include "./headers/GameManagement.h"

GameManagement::GameManagement(std::vector<Player> players) 
    : players(players), currentPlayerIndex(0), gameOver(false) {
    deck.shuffle();
    communityCards.clear();
}

void GameManagement::startNewRound() {
    for (Player&player : players) {
        player.clearHand();
    }
    communityCards.clear();
    deck.shuffle();
}

void GameManagement::dealCards() {
    for (Player&player : players) {
        player.receiveCard(deck.dealCard());
        player.receiveCard(deck.dealCard());
    }
}

void GameManagement::dealCommunityCards(int numCards) {
    for (int i = 0; i < numCards; ++i) {
        communityCards.push_back(deck.dealCard());
    }
}

// void GameManagement::bettingRound() { 
//     for (Player&player : players) {
//         player.takeTurn();
//     }
// }


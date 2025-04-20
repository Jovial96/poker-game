#pragma once
#include "PokerGame.h"
#include "Deck.h"
#include "Player.h"

void PokerGame::addPlayer(const std::string& name) {
    players.emplace_back(name);
}

void PokerGame::startGame() {
    deck = Deck();
    deck.shuffle();

    for (Player& player : players) {
        player.clearHand();
        player.receiveCard(deck.dealCard());
        player.receiveCard(deck.dealCard());
    }

    communityCards.clear();

    for (const Player& player : players) {
        std::cout << "Player hand:\n";
        player.showHand();
        std::cout << std::endl;
    }
}

void PokerGame::dealFlop() {
    for (int i = 0; i < 3; i++) {
        communityCards.push_back(deck.dealCard());
    }
}

void PokerGame::dealTurn() {
    communityCards.push_back(deck.dealCard());
}

void PokerGame::dealRiver() {
    communityCards.push_back(deck.dealCard());
}

std::ostream& operator<<(std::ostream&os, const std::vector<Card>& communityCards) {
    for (const Card&card : communityCards) {
        os << card << " ";
    }

    return os;
}

void PokerGame::showCommunityCards() {
    std::cout << "Community Cards: ";
    std::cout << communityCards << std::endl;
}

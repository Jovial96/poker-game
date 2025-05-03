#include "PokerGame.h"
#include "Deck.h"
#include "Player.h"
#include "GameState.h"
#include <limits>

void PokerGame::addPlayer(const std::string& name, int initialChips) {
    players.emplace_back(name, initialChips);
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

void PokerGame::bettingRound() {
    GameState state(players);  

    std::cout << "Enter betting round" << "\n";

    std::cout << state.isRoundOver() << "\n";

    while (!state.isRoundOver()) {
        Player& player = state.getCurrentPlayer();

        if (player.hasFolded() || player.getChips() == 0) {
            state.advanceTurn();
            continue;
        }

        std::cout << "\n" << player.getName() << "'s turn. Chips: " << player.getChips() << "\n";
        std::cout << "Current bet: " << state.getCurrentBet()
                  << ", Your bet: " << player.getCurrentBet() << "\n";
        std::cout << "Choose action (1 = Fold, 2 = Call, 3 = Raise): ";

        int action;
        while (!(std::cin >> action) || (action < 1 || action > 3)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter 1, 2, or 3: ";
        }

        if (action == 1) {
            state.foldCurrentPlayer();
            std::cout << player.getName() << " folds.\n";
        } else if (action == 2) {
            int callAmount = state.getCurrentBet() - player.getCurrentBet();
            if (callAmount > player.getChips()) callAmount = player.getChips();  // all-in
            state.collectBet(player, callAmount);
            std::cout << player.getName() << " calls " << callAmount << ".\n";
        } else if (action == 3) {
            std::cout << "Enter raise amount: ";
            int raiseAmount;
            while (!(std::cin >> raiseAmount) || raiseAmount < 1) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid raise amount. Try again: ";
            }

            int callAmount = state.getCurrentBet() - player.getCurrentBet();
            int totalBet = callAmount + raiseAmount;
            if (totalBet > player.getChips()) totalBet = player.getChips();  // all-in

            state.collectBet(player, totalBet);
            state.setCurrentBet(player.getCurrentBet());

            std::cout << player.getName() << " raises by " << raiseAmount << " (total bet: " << totalBet << ").\n";
        }

        state.advanceTurn();
    }

    std::cout << "\nBetting round over. Pot: " << state.getPotSize() << "\n";
}
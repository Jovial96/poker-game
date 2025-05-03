#include <iostream>
#include "PokerGame.h"

int main() {
    PokerGame game;

    std::cout << "Welcome to the Poker Game!\n";

    // Add players manually
    int numPlayers;
    std::cout << "Enter number of players: ";
    std::cin >> numPlayers;

    for (int i = 0; i < numPlayers; ++i) {
        std::string name;
        std::cout << "Enter name for player " << (i + 1) << ": ";
        std::cin >> name;
        game.addPlayer(name, 100);  // start everyone with 100 chips
    }
    
    std::cout << "\n=== Starting Game ===\n";
    game.startGame();

    std::cout << "\n=== Pre-Flop Betting ===\n";
    game.bettingRound();  // accepts user input inside

    game.dealFlop();
    std::cout << "\n=== Flop Betting ===\n";
    game.showCommunityCards();
    game.bettingRound();

    game.dealTurn();
    std::cout << "\n=== Turn Betting ===\n";
    game.showCommunityCards();
    game.bettingRound();

    game.dealRiver();
    std::cout << "\n=== River Betting ===\n";
    game.showCommunityCards();
    game.bettingRound();

    std::cout << "\nGame over (no winner logic yet).\n";

    return 0;
}
#include <iostream>
#include "./headers/PokerGame.h"
#include <vector>

int main() {
    PokerGame game;

    game.addPlayer("Jovial", 100);
    game.addPlayer("Yu Heng", 100);

    game.startGame();

    game.dealFlop();
    game.dealTurn();
    game.dealRiver();

    game.showCommunityCards();

    return 0;
}


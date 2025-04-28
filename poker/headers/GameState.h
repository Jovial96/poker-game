#ifndef __GAMESTATE__
#define __GAMESTATE__

#include <vector>
#include "Player.h"

class GameState {
private:
    std::vector<Player> players;
    int currentBet;
    int potSize;
    size_t currentPlayerIndex;
    bool roundOver;

public:
    GameState(int numPlayers, int start)
};

#endif
#ifndef __GAMESTATE__
#define __GAMESTATE__

#include <vector>
#include "Player.h"

class GameState {
private:
    std::vector<Player>& players;
    int currentBet;
    int potSize;
    size_t currentPlayerIndex;
    bool roundOver;
    bool anyActionTaken;

public:
    GameState(std::vector<Player>& players);

    Player& getCurrentPlayer();
    void advanceTurn();
    bool isRoundOver() const;

    void resetRound();
    void collectBet(Player& player, int amount);
    void foldCurrentPlayer();

    const std::vector<Player>& getPlayers() const;
    std::vector<Player>& getPlayers();

    int getCurrentBet();
    void setCurrentBet(int bet);
    int getPotSize() const;
    void addToPot(int amount);

    size_t getCurrentPlayerIndex() const;
};

#endif
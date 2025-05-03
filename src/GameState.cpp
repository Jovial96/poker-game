#include "GameState.h"
#include "Player.h"
#include <algorithm>
#include <vector>

GameState::GameState(std::vector<Player>& players)
    : players(players), currentBet(0), potSize(0), currentPlayerIndex(0), roundOver(false), anyActionTaken(false) {}

Player& GameState::getCurrentPlayer() {
    return players[currentPlayerIndex];
}

void GameState::advanceTurn() {
    size_t startingIndex = currentPlayerIndex;
    do {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    } while ((players[currentPlayerIndex].hasFolded() || players[currentPlayerIndex].getChips() == 0) && currentPlayerIndex != startingIndex);
}

bool GameState::isRoundOver() const {
    if (!anyActionTaken) return false;

    int activePlayers = 0;
    int matchedBets = 0;
    int expectedBet = currentBet;

    for (const Player& player : players) {
        if (!player.hasFolded() && player.getChips() > 0) {
            activePlayers++;
            if (player.getCurrentBet() == expectedBet) {
                matchedBets++;
            }
        }
    }

    return (activePlayers <= 1) || (matchedBets == activePlayers);
}

void GameState::resetRound() {
    currentBet = 0;
    for (Player& player: players) {
        player.setCurrentBet(0);
    }
}

void GameState::collectBet(Player& player, int amount) {
    int actualAmount = std::min(player.getChips(), amount);
    player.decreaseChips(actualAmount);
    player.setCurrentBet(player.getCurrentBet() + actualAmount);
    potSize += amount;
    anyActionTaken = true;
}

void GameState::foldCurrentPlayer() {
    players[currentPlayerIndex].setHasFolded(true);
    anyActionTaken = true;
}

const std::vector<Player>& GameState::getPlayers() const {
    return players;
}

std::vector<Player>& GameState::getPlayers() {
    return players;
}

int GameState::getCurrentBet() {
    return currentBet;
}

void GameState::setCurrentBet(int bet) {
    currentBet = bet;
}

int GameState::getPotSize() const {
    return potSize;
}

void GameState::addToPot(int amount) {
    potSize += amount;
}

size_t GameState::getCurrentPlayerIndex() const {
    return currentPlayerIndex;
}
#include "./headers/GameState.h"

GameState::GameState(int numPlayers, int startingChips) 
    : currentBet(0), potSize(0), currentPlayerIndex(0), roundOver(false) {}

void GameState::addPlayer(const std::string& name, int chips) {
    players.emplace_back(name, chips);
}

void GameState::startNewRound() {
    currentBet = 0;
    potSize = 0;
    roundOver = false;

    for (Player& player : players) {
        player.resetForNewRound();
    }
}

void GameState::updatePot(int betAmount) {
    potSize += betAmount;
}

void GameState::setCurrentBet(int betAmount) {
    currentBet += betAmount;
}

void GameState::nextTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
} 

const std::vector<Player>& GameState::getPlayers() const {
    return players;
}

Player& GameState::getCurrentPlayer() {
    return players[currentPlayerIndex];
}

int GameState::getCurrentBet() const {
    return currentBet;
}

int GameState::getPotSize() const {
    return potSize;
}

bool GameState::isRoundOver() const {
    return roundOver;
}
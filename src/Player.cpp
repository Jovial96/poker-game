#include "Player.h"

Player::Player(const std::string& name, int initialChips) 
    : name(name), chips(initialChips), folded(false), currentBet(0) {}

void Player::receiveCard(const Card& card) {
    hand.push_back(card);
}

void Player::showHand() const {
    for (const Card& card: hand) {
        std::cout<< card << " ";
    }
    std::cout << std::endl;
}

void Player::clearHand() {
    hand.clear();
    folded = false;
    currentBet = 0;
}

bool Player::hasFolded() const {
    return folded;
}

void Player::setHasFolded(bool f) {
    folded = f;
}

int Player::getChips() const {
    return chips;
}

void Player::decreaseChips(int amount) {
    chips -= amount;
}

int Player::getCurrentBet() const {
    return currentBet;
}

void Player::setCurrentBet(int amount) {
    currentBet = amount;
}

const std::string& Player::getName() const {
    return name;
}
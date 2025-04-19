#include <iostream>
#include "Player.h"
#include "Card.h"
#include <string>

Player::Player(const std::string& name) : name(name) {}

void Player::receiveCard(const Card& card) {
    hand.push_back(card);
}

void Player::showHand() const {
    for (const Card& card : hand) {
        std::cout << card;
    }
}

void Player::clearHand() {
    hand.clear();
}
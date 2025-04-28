#pragma once    
#include <iostream>
#include "Player.h"
#include "Card.h"
#include <string>

Player::Player(const std::string& name, int initialChips)
    : name(name), chips(initialChips), folded(false), currentBet(0) {}

void Player::bet(int amount) {
    if (amount <= chips) {
        currentBet += amount;
        chips -= amount;
        std::cout << name << " bets " << amount << " chips" << std::endl;
    } else {
        std::cout << name << " does not have enough chips" << std::endl;
    }
}

void Player::fold() {
    folded = true;
    std::cout << name << " has folded" << std::endl;
}

void Player::check() {
    std::cout << name << " checks";
}

void Player::call(int amount) {
    if (amount <= chips) {
        currentBet += amount;
        chips -= amount;
        chips -= amount;
        std::cout << name << "calls the bet of " << amount << std::endl;
    } else {
        std::cout << name << " does not have enough chips " << std::endl;
    }
}

void Player::raise(int amount) {
    if (amount <= chips) {
        currentBet += amount;
        chips -= amount;
        std::cout << name << " raise " << amount << std::endl;
    } else {
        std::cout << name << " does not have enough chips to raise" << std::endl;
    }
}

int Player::getChips(){
    return chips;
}

int Player::getCurrentBet() {
    return currentBet;
}

bool Player::isFolded() {
    return folded;
}

// void Player::takeTurn(const GameState& state) {
//     std::cout << name << "'s turn. Available chips: " << chips << "\n";
// }

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
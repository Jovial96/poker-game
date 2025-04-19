#pragma once
#include "Deck.h"
#include "Card.h"
#include <random>

Deck::Deck() {
    for (int s = 0; s <= 4; s++) {
        for (int r = 2; r <= 14; r++) {
            cards.emplace_back(static_cast<Rank>(r), static_cast<Suit>(s));
        }
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::dealCard() {
    if (cards.empty()) {
        throw std::out_of_range("No more cards in deck!");
    }
    Card top = cards.back();
    cards.pop_back();
    return top;
}

bool Deck::isEmpty() const {
    return cards.empty();
}
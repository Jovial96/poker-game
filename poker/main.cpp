#include "./headers/HandEvaluator.h"
#include "./headers/Card.h"
#include "./headers/CardTypes.h"
#include <iostream>

int main() {
    std::vector<Card> fiveCards;
    fiveCards.push_back(Card(Rank::Ace, Suit::Clubs));
    fiveCards.push_back(Card(Rank::Ace, Suit::Spades));
    fiveCards.push_back(Card(Rank::King, Suit::Spades));
    fiveCards.push_back(Card(Rank::Queen, Suit::Clubs));
    fiveCards.push_back(Card(Rank::King, Suit::Clubs));

    std::cout << HandEvaluator::evaluateFiveCardHand(fiveCards) << std::endl;
    return 0;
}


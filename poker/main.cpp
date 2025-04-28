#include "./headers/HandEvaluator.h"
#include "./headers/Card.h"
#include "./headers/CardTypes.h"
#include <iostream>

int main() {
    std::vector<Card> handA;
    handA.push_back(Card(Rank::Ace, Suit::Clubs));
    handA.push_back(Card(Rank::Two, Suit::Clubs));
    handA.push_back(Card(Rank::Three, Suit::Clubs));
    handA.push_back(Card(Rank::Four, Suit::Clubs));
    handA.push_back(Card(Rank::Five, Suit::Clubs));
    handA.push_back(Card(Rank::Seven, Suit::Clubs));
    handA.push_back(Card(Rank::Eight, Suit::Clubs));

    std::vector<Card> handB;
    handB.push_back(Card(Rank::Ace, Suit::Clubs));
    handB.push_back(Card(Rank::King, Suit::Spades));
    handB.push_back(Card(Rank::Four, Suit::Diamonds));
    handB.push_back(Card(Rank::Six, Suit::Clubs));
    handB.push_back(Card(Rank::Five, Suit::Clubs));
    handB.push_back(Card(Rank::Nine, Suit::Clubs));
    handB.push_back(Card(Rank::Jack, Suit::Clubs));

    EvaluatedHand EvaluatedHandA = HandEvaluator::findBestHand(handA);
    EvaluatedHand EvaluatedHandB = HandEvaluator::findBestHand(handB);

    int result = HandEvaluator::compareHands(EvaluatedHandA, EvaluatedHandB);

    if (result == 1) {
        std::cout << "PlayerA wins!" << std::endl;
    } else if (result == -1) {
        std::cout << "PlayerB wins!" << std::endl;
    } else {
        std::cout << "It's a tie!" << std::endl;
    }
}


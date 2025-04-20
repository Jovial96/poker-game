#pragma once
#include <vector>
#include "Card.h"

enum class HandRank {
    HighCard = 1,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush
};

struct EvaluatedHand {
    HandRank rank;
    std::vector<int> tiebreakers;
};

class HandEvaluator {
public:
    static EvaluatedHand evaluate(const std::vector<Card>& cards);
private:
    static EvaluatedHand evaluateFiveCardHand(const std::vector<Card>& hand);

    //Helper Function 
    static bool isFlush(const std::vector<Card>& cards);
    static bool isStraight(const std::vector<Card>& cards);
    static bool isStraightFlush(const std::vector<Card>& cards);
};


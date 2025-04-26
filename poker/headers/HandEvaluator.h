#ifndef __HandEvaluator__
#define __HandEvaluator__

#include <vector>
#include "Card.h"
#include <unordered_map>

enum class HandRank {
    HighCard = 1,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    Quads,
    StraightFlush,
    RoyalFlush
};

struct EvaluatedHand {
    HandRank rank;
    std::vector<int> tiebreakers;
};

std::ostream& operator<<(std::ostream&os, const EvaluatedHand& hand);

class HandEvaluator {
public:
    static EvaluatedHand evaluate(const std::vector<Card>& cards);
    static EvaluatedHand evaluateFiveCardHand(const std::vector<Card>& cards);
private:
    //Helper Function 
    static bool isFlush(const std::vector<Card>& cards);
    static bool isStraight(const std::vector<Card>& cards);
    static bool isStraightFlush(const std::vector<Card>& cards);
    static bool isRoyalFlush(const std::vector<Card>& cards);
    static bool isPair(const std::unordered_map<int, int>& valueCounts);
    static bool isTwoPair(const std::unordered_map<int, int>& valueCounts);
    static bool isThreeOfAKind(const std::unordered_map<int, int>& valueCounts);
    static bool isQuads(const std::unordered_map<int, int>& valueCounts);
    static bool isFullHouse(const std::unordered_map<int, int>& valueCounts);
    static std::unordered_map<int, int> getValueCounts(const std::vector<Card>& cards);
};

#endif
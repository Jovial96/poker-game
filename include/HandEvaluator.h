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

struct HandDetectionResult {
    bool isMatch = false;
    std::vector<int> tiebreakerCards = {};
};

struct EvaluatedHand {
    HandRank rank;
    std::vector<int> tiebreakers;
};

std::ostream& operator<<(std::ostream&os, const EvaluatedHand& hand);

class HandEvaluator {
public:
    static EvaluatedHand findBestHand(const std::vector<Card>& cards);
    static EvaluatedHand evaluateFiveCardHand(const std::vector<Card>& cards);
    static int compareHands(const EvaluatedHand& handA, const EvaluatedHand& handB);
private:
    //Helper Function 
    static HandDetectionResult isFlush(const std::vector<Card>& cards);
    static HandDetectionResult isStraight(const std::vector<Card>& cards);
    static HandDetectionResult isStraightFlush(const std::vector<Card>& cards);
    static HandDetectionResult isRoyalFlush(const std::vector<Card>& cards);
    static HandDetectionResult isPair(const std::unordered_map<int, int>& valueCounts);
    static HandDetectionResult isTwoPair(const std::unordered_map<int, int>& valueCounts);
    static HandDetectionResult isThreeOfAKind(const std::unordered_map<int, int>& valueCounts);
    static HandDetectionResult isQuads(const std::unordered_map<int, int>& valueCounts);
    static HandDetectionResult isFullHouse(const std::unordered_map<int, int>& valueCounts);
    static std::unordered_map<int, int> getValueCounts(const std::vector<Card>& cards);
};

#endif
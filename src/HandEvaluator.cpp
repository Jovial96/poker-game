#include "HandEvaluator.h"
#include "Card.h"
#include "CardTypes.h"
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>

HandDetectionResult HandEvaluator::isFlush(const std::vector<Card>& cards) {
    HandDetectionResult result;
    if (cards.empty() || cards.size() != 5) {
        result.isMatch = false;
        return result;
    }
    
    Suit suit = cards[0].getSuit();
    for (const Card& card : cards) {
        if (card.getSuit() != suit) {
            result.isMatch = false;
            return result;
        }
    }
    result.isMatch = true;

    for (const Card& card : cards) {
        result.tiebreakerCards.push_back(static_cast<int>(card.getRank()));
    }
    std::sort(result.tiebreakerCards.begin(), result.tiebreakerCards.end(), std::greater<int>());

    return result;
}

HandDetectionResult HandEvaluator::isStraight(const std::vector<Card>& cards) {
    HandDetectionResult result;
    if (cards.size() != 5) {
        result.isMatch = false;
        return result;
    }

    std::set<int> uniqueRanks;

    for (const Card& card : cards) {
        uniqueRanks.insert(static_cast<int>(card.getRank()));
    }

    if (uniqueRanks.count(14)) {
        uniqueRanks.insert(1);
    }

    std::vector<int> sortedRanks(uniqueRanks.begin(), uniqueRanks.end());

    for (size_t i = 0; i + 4 < sortedRanks.size(); ++i) {
        if (sortedRanks[i] + 1 == sortedRanks[i + 1] &&
            sortedRanks[i] + 2 == sortedRanks[i + 2] &&
            sortedRanks[i] + 3 == sortedRanks[i + 3] &&
            sortedRanks[i] + 4 == sortedRanks[i + 4]) {
                result.isMatch = true;
                result.tiebreakerCards.push_back(sortedRanks[i + 4]);
                return result;
            }
    }
    result.isMatch = false;
    return result;
}

HandDetectionResult HandEvaluator::isStraightFlush(const std::vector<Card>& cards) {
    HandDetectionResult result;
    HandDetectionResult flushResult = isFlush(cards);
    if (!flushResult.isMatch) {
        result.isMatch = false;
        return result;
    }

    HandDetectionResult straightResult = isStraight(cards);
    if (!straightResult.isMatch) { 
        result.isMatch = false;
        return result;
    }

    return straightResult;
}

HandDetectionResult HandEvaluator::isRoyalFlush(const std::vector<Card>& cards) {
    HandDetectionResult result;
    HandDetectionResult straightFlushResult = isStraightFlush(cards);
    if (!straightFlushResult.isMatch) {
        result.isMatch = false;
        return result;
    }

    if (straightFlushResult.tiebreakerCards[0] == 14) {
        result.isMatch = true;
        return result;
    }

    return result;
}

HandDetectionResult HandEvaluator::isPair(const std::unordered_map<int, int>& valueCounts) {
    HandDetectionResult result;
    int pairCount = 0;
    std::vector<int> kickers;
    int pairRank = -1;

    for (const auto& [rank, count] : valueCounts) {
        if (count == 2) {
            pairCount++;
            pairRank = rank;
        } else {
            kickers.push_back(rank);
        }
    }

    if (pairCount == 1) {
        result.isMatch = true;
        result.tiebreakerCards.push_back(pairRank);
        std::sort(kickers.begin(), kickers.end(), std::greater<>());
        result.tiebreakerCards.insert(result.tiebreakerCards.end(), kickers.begin(), kickers.end());
    }

    return result;
}

HandDetectionResult HandEvaluator::isTwoPair(const std::unordered_map<int, int>& valueCounts) {
    HandDetectionResult result;
    int pairCount = 0;
    std::vector<int> kickers;
    std::vector<int> pairs;

    for (const auto& [rank, count] : valueCounts) {
        if (count == 2) {
            pairCount++;
            pairs.push_back(rank);
        } else {
            kickers.push_back(rank);
        }
    }

    if (pairCount == 2) {
        result.isMatch = true;
        std::sort(pairs.begin(), pairs.end(), std::greater<>());
        result.tiebreakerCards.insert(result.tiebreakerCards.end(), pairs.begin(), pairs.end());
        std::sort(kickers.begin(), kickers.end(), std::greater<>());
        result.tiebreakerCards.insert(result.tiebreakerCards.end(), kickers.begin(), kickers.end());
    }

    return result;
}

HandDetectionResult HandEvaluator::isThreeOfAKind(const std::unordered_map<int, int>& valueCounts) {
    HandDetectionResult result;
    int tripsCount = 0;
    std::vector<int> kickers;
    std::vector<int> trips;

    for (const auto& [rank, count] : valueCounts) {
        if (count == 3) {
            tripsCount++;
            trips.push_back(rank);
        } else {
            kickers.push_back(rank);
        }
    }

    if (tripsCount == 1) {
        result.isMatch = true;
        std::sort(trips.begin(), trips.end(), std::greater<>());
        result.tiebreakerCards.insert(result.tiebreakerCards.end(), trips.begin(), trips.end());
        std::sort(kickers.begin(), kickers.end(), std::greater<>());
        result.tiebreakerCards.insert(result.tiebreakerCards.end(), kickers.begin(), kickers.end());
    }

    return result;
}

HandDetectionResult HandEvaluator::isQuads(const std::unordered_map<int, int>& valueCounts) {
    HandDetectionResult result;
    int quadRank = -1;
    std::vector<int> kickers;

    for (const auto& [rank, count] : valueCounts) {
        if (count == 4) {
            quadRank = rank;
        } else {
            kickers.push_back(rank);
        }
    }

    if (quadRank != -1) {
        result.isMatch = true;
        result.tiebreakerCards.push_back(quadRank); // Quad rank first

        std::sort(kickers.begin(), kickers.end(), std::greater<>());
        result.tiebreakerCards.insert(result.tiebreakerCards.end(), kickers.begin(), kickers.end());
    }

    return result;
}

HandDetectionResult HandEvaluator::isFullHouse(const std::unordered_map<int, int>& valueCounts) {
    HandDetectionResult result;
    int tripRank = -1;
    int pairRank = -1;

    for (const auto& [rank, count] : valueCounts) {
        if (count == 3) {
            tripRank = rank;
        } else if (count == 2) {
            pairRank = rank;
        }
    }

    if (tripRank != -1 && pairRank != -1) {
        result.isMatch = true;
        result.tiebreakerCards.push_back(tripRank); 
        result.tiebreakerCards.push_back(pairRank); 
    }

    return result;
}

std::unordered_map<int, int> HandEvaluator::getValueCounts(const std::vector<Card>& cards) {
    std::unordered_map<int, int> valueCounts;
    for (const Card& card: cards) {
        valueCounts[static_cast<int>(card.getRank())]++;
    }

    return valueCounts;
}

EvaluatedHand HandEvaluator::evaluateFiveCardHand(const std::vector<Card>& cards) {
    EvaluatedHand result;
    std::unordered_map<int, int> valueCounts = getValueCounts(cards);

    HandDetectionResult royalFlushResult = isRoyalFlush(cards);
    if (royalFlushResult.isMatch) {
        result.rank = HandRank::RoyalFlush;
        result.tiebreakers = royalFlushResult.tiebreakerCards;
        return result;
    }

    HandDetectionResult straightFlushResult = isStraightFlush(cards);
    if (straightFlushResult.isMatch) {
        result.rank = HandRank::StraightFlush;
        result.tiebreakers = straightFlushResult.tiebreakerCards;
        return result;
    }

    HandDetectionResult quadsResult = isQuads(valueCounts);
    if (quadsResult.isMatch) {
        result.rank = HandRank::Quads;
        result.tiebreakers = quadsResult.tiebreakerCards;
        return result;
    }

    HandDetectionResult fullHouseResult = isFullHouse(valueCounts);
    if (fullHouseResult.isMatch) {
        result.rank = HandRank::FullHouse;
        result.tiebreakers = fullHouseResult.tiebreakerCards;
        return result;
    }

    HandDetectionResult flushResult = isFlush(cards);
    if (flushResult.isMatch) {
        result.rank = HandRank::Flush;
        result.tiebreakers = flushResult.tiebreakerCards;
        return result;
    }

    HandDetectionResult straightResult = isStraight(cards);
    if (straightResult.isMatch) {
        result.rank = HandRank::Straight;
        result.tiebreakers = straightResult.tiebreakerCards;
        return result;
    }

    HandDetectionResult tripsResult = isThreeOfAKind(valueCounts);
    if (tripsResult.isMatch) {
        result.rank = HandRank::ThreeOfAKind;
        result.tiebreakers = tripsResult.tiebreakerCards;
        return result;
    }

    HandDetectionResult twoPairResult = isTwoPair(valueCounts);
    if (twoPairResult.isMatch) {
        result.rank = HandRank::TwoPair;
        result.tiebreakers = twoPairResult.tiebreakerCards;
        return result;
    }
    
    HandDetectionResult pairResult = isPair(valueCounts);
    if (pairResult.isMatch) {
        result.rank = HandRank::OnePair;
        result.tiebreakers = pairResult.tiebreakerCards;
        return result;
    }

    result.rank = HandRank::HighCard;

    std::vector<int> highCards;
    for (const Card& card : cards) {
        highCards.push_back(static_cast<int>(card.getRank()));
    }
    std::sort(highCards.begin(), highCards.end(), std::greater<>());
    result.tiebreakers = highCards;

    return result;
}

std::ostream& operator<<(std::ostream&os, const EvaluatedHand& hand) {
    static const std::unordered_map<HandRank, std::string> rankToString = {
        {HandRank::HighCard, "High Card"},
        {HandRank::OnePair, "One Pair"},
        {HandRank::TwoPair, "Two Pair"},
        {HandRank::ThreeOfAKind, "Three of a Kind"},
        {HandRank::Straight, "Straight"},
        {HandRank::Flush, "Flush"},
        {HandRank::FullHouse, "Full House"},
        {HandRank::Quads, "Four of a Kind"},
        {HandRank::StraightFlush, "Straight Flush"},
        {HandRank::RoyalFlush, "Royal Flush"}
    };

    os << "HandRank: " << rankToString.at(hand.rank);

    return os;
}

int HandEvaluator::compareHands(const EvaluatedHand& evaluatedHandA, const EvaluatedHand& evaluatedHandB) {
    if (evaluatedHandA.rank > evaluatedHandB.rank) {
        return 1;
    }

    if (evaluatedHandA.rank < evaluatedHandB.rank) {
        return -1;
    }

    for (size_t i = 0; i < std::min(evaluatedHandA.tiebreakers.size(), evaluatedHandB.tiebreakers.size()); ++i) {
        if (evaluatedHandA.tiebreakers[i] > evaluatedHandB.tiebreakers[i]) {
            return 1;
        }
        if (evaluatedHandA.tiebreakers[i] < evaluatedHandB.tiebreakers[i]) {
            return -1;
        }
    }

    return 0;
}

EvaluatedHand HandEvaluator::findBestHand(const std::vector<Card>& cards) {
    EvaluatedHand bestHand;  
    int bestRank = -1;
    std::vector<int> bestKickers;

    std::vector<int> indices = {0, 1, 2, 3, 4, 5, 6};

    std::vector<bool> combination(7, false);
    std::fill(combination.begin(), combination.begin() + 5, true);

    do {
        std::vector<Card> fiveCards;
        for (int i = 0; i < 7; ++i) {
            if (combination[i]) {
                fiveCards.push_back(cards[i]);
            }
        }

        EvaluatedHand evaluatedHand = HandEvaluator::evaluateFiveCardHand(fiveCards);

        if (static_cast<int>(evaluatedHand.rank) > bestRank || 
            (static_cast<int>(evaluatedHand.rank) == bestRank && evaluatedHand.tiebreakers > bestKickers)) {
            bestRank = static_cast<int>(evaluatedHand.rank);
            bestHand = evaluatedHand; 
        }
    } while (std::prev_permutation(combination.begin(), combination.end()));

    return bestHand;
}
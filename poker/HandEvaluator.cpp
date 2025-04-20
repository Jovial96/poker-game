#include "HandEvaluator.h"
#include "Card.h"
#include "CardTypes.h"
#include <vector>
#include <algorithm>
#include <set>
#include <map>

static bool isFlush(const std::vector<Card>& cards) {
    if (cards.empty() || cards.size() < 5) return false;
    
    Suit suit = cards[0].getSuit();
    for (const Card& card : cards) {
        if (card.getSuit() != suit) {
            return false;
        }
    }
    return true;
}

static bool isStraight(const std::vector<Card>& cards) {
    if (cards.empty() || cards.size() < 5) return false;
    
    std::sort(cards.begin(), cards.end(), [](const Card& cardA, const Card& cardB) { return cardA.getRank() > cardB.getRank(); });

    std::set<Rank> seenRanks;

    for (const Card& card : cards) {
        if (seenRanks.find(card.getRank()) == seenRanks.end()) {
            seenRanks.insert(card.getRank());
        }
    }

    std::vector<int> rankVals;

    if (seenRanks.count(Rank::Ace)) {
        rankVals.push_back(1);
    }

    for (Rank r : seenRanks) {
        rankVals.push_back(static_cast<int>(r));
    }

    std::sort(rankVals.begin(), rankVals.end(), std::greater<int>());

    for (int i = 0; i <= rankVals.size() - 5; i++) {
        bool isSequence = true;

        for (int j = 0; j < 4; j++) {
            if (rankVals[i + j] != rankVals[i + j + 1] + 1) {
                isSequence = false;
                break;
            }
        }

        if (isSequence) return true;
    }

    return false;
}

static bool isStraightFlush(const std::vector<Card>& cards) {
    if (!isFlush(cards)) {
        return false;
    }

    return isStraight(cards);
}

static std::map<int, int> getValueCounts(const std::vector<Card>& cards) {
    std::map<int, int> valueCounts;
    for (const Card& card: cards) {
        valueCounts[static_cast<int>(card.getRank())]++;
    }

    return valueCounts;
}
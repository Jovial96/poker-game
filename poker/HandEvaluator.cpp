#include "./headers/HandEvaluator.h"
#include "./headers/Card.h"
#include "./headers/CardTypes.h"
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>

bool HandEvaluator::isFlush(const std::vector<Card>& cards) {
    if (cards.empty() || cards.size() != 5) return false;
    
    Suit suit = cards[0].getSuit();
    for (const Card& card : cards) {
        if (card.getSuit() != suit) {
            return false;
        }
    }
    return true;
}

bool HandEvaluator::isStraight(const std::vector<Card>& cards) {
    if (cards.size() != 5) return false;

    std::set<int> uniqueRanks;

    for (const Card& card : cards) {
        uniqueRanks.insert(static_cast<int>(card.getRank()));
    }

    if (uniqueRanks.count(14)) {
        uniqueRanks.insert(1);
    }

    std::vector<int> sortedRanks(uniqueRanks.begin(), uniqueRanks.end());
    std::sort(sortedRanks.begin(), sortedRanks.end());

    for (size_t i = 0; i + 4 < sortedRanks.size(); ++i) {
        if (sortedRanks[i] + 1 == sortedRanks[i + 1] &&
            sortedRanks[i] + 2 == sortedRanks[i + 2] &&
            sortedRanks[i] + 3 == sortedRanks[i + 3] &&
            sortedRanks[i] + 4 == sortedRanks[i + 4]) {
                return true;
            }
    }

    return false;
}

bool HandEvaluator::isStraightFlush(const std::vector<Card>& cards) {
    if (!isFlush(cards)) {
        return false;
    }

    return isStraight(cards);
}

bool HandEvaluator::isRoyalFlush(const std::vector<Card>& cards) {
    if (!isStraightFlush(cards)) {
        return false;
    }

    std::set<int> royalRanks {10, 11, 12, 13, 14};

    for (const Card&card : cards) {
        royalRanks.erase(static_cast<int>(card.getRank()));
    }

    return royalRanks.empty();
}

bool HandEvaluator::isPair(const std::unordered_map<int, int>& valueCounts) {

    int pairs = 0;
    for (const auto& [rank, count] : valueCounts) {
        if (count == 2) {
            pairs++;
        }
    }

    return pairs == 1;
}

bool HandEvaluator::isTwoPair(const std::unordered_map<int, int>& valueCounts) {

    int pairs = 0;
    for (const auto& [rank, count] : valueCounts) {
        if (count == 2) {
            pairs++;
        }
    }

    return pairs == 2;
}

bool HandEvaluator::isThreeOfAKind(const std::unordered_map<int, int>& valueCounts) {
    int threeOfAKind = 0;
    for (const auto& [rank, count] : valueCounts) {
        if (count == 3) {
            threeOfAKind++;
        }
    }

    std::cout << threeOfAKind << std::endl;

    return threeOfAKind == 1;
}

bool HandEvaluator::isQuads(const std::unordered_map<int, int>& valueCounts) {
    int quads= 0;
    for (const auto& [rank, count] : valueCounts) {
        if (count == 4) {
            quads++;
        }
    }

    return quads == 1;
}

bool HandEvaluator::isFullHouse(const std::unordered_map<int, int>& valueCounts) {
    int threeRank = -1;
    int pairRank = -1;

    for (const auto& [rank, count] : valueCounts) {
        if (count >= 3 && rank > threeRank) {
            threeRank = rank;
        }
    }

    for (const auto& [rank, count] : valueCounts) {
        if (rank != threeRank && count >= 2 && rank > pairRank) {
            pairRank = rank;
        }
    }

    return threeRank != -1 && pairRank != -1;
}

std::unordered_map<int, int> HandEvaluator::getValueCounts(const std::vector<Card>& cards) {
    std::unordered_map<int, int> valueCounts;
    for (const Card& card: cards) {
        valueCounts[static_cast<int>(card.getRank())]++;
    }

    // Debug print: Display value counts
    std::cout << "Value Counts:\n";
    for (const auto& [rank, count] : valueCounts) {
        std::cout << "Rank: " << rank << ", Count: " << count << std::endl;
    }

    return valueCounts;
}

EvaluatedHand HandEvaluator::evaluateFiveCardHand(const std::vector<Card>& cards) {
    std::unordered_map<int, int> valueCounts = getValueCounts(cards);
    
    std::cout << "Evaluating Hand" << std::endl;

    if (isRoyalFlush(cards)) {
        std::cout << "Royal Flush" << std::endl;
        return {HandRank::RoyalFlush};
    } else if (isStraightFlush(cards)) {
        std::cout << "Straight Flush" << std::endl;
        return {HandRank::StraightFlush}; 
    } else if (isQuads(valueCounts)) {
        std::cout << "Quads" << std::endl;
        return {HandRank::Quads};
    } else if (isFullHouse(valueCounts)) {
        std::cout << "Full House" << std::endl;
        return {HandRank::FullHouse};
    } else if (isFlush(cards)) {
        std::cout << "Flush" << std::endl;
        return {HandRank::Flush};
    } else if (isThreeOfAKind(valueCounts)) {
        std::cout << "Three of a kind" << std::endl;
        return {HandRank::ThreeOfAKind};
    } else if (isStraight(cards)) {
        std::cout << "Straight" << std::endl;
        return {HandRank::Straight};
    } else if (isTwoPair(valueCounts)) {
        std::cout << "Two Pair" << std::endl;
        return {HandRank::TwoPair};
    } else if (isPair(valueCounts)) {
        std::cout << "Pair" << std::endl;
        return {HandRank::OnePair};
    } else {
        return {HandRank::HighCard};
    }
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
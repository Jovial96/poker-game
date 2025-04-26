#include "./headers/Card.h"
#include <iostream>
#include <string>

Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

Rank Card::getRank() const {
    return rank;
}

Suit Card::getSuit() const {
    return suit;
}

std::string rankToString(Rank rank) {
    switch(rank) {
        case Rank::Two: return "2";
        case Rank::Three: return "3";
        case Rank::Four: return "4";
        case Rank::Five: return "5";
        case Rank::Six: return "6";
        case Rank::Seven: return "7";
        case Rank::Eight: return "8";
        case Rank::Nine: return "9";
        case Rank::Ten: return "10";
        case Rank::Jack: return "Jack";
        case Rank::Queen: return "Queen";
        case Rank::King: return "King";
        case Rank::Ace: return "Ace";
        default: return "?";
    }
}

std::string suitToString(Suit suit) {
    switch(suit) {
        case Suit::Clubs: return "Clubs";
        case Suit::Diamonds: return "Diamonds";
        case Suit::Hearts: return "Hearts";
        case Suit::Spades: return "Spaces";
        default: return "?";
    }
}

std::ostream& operator<<(std::ostream&os, const Card& card) {
    os << rankToString(card.rank) << " of " << suitToString(card.suit);
    return os;
}
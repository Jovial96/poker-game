#pragma once    
#include "CardTypes.h"
#include <iostream>

class Card {
private:
    Rank rank;
    Suit suit;
public:
    Card(Rank r, Suit s);
    Rank getRank() const;
    Suit getSuit() const;

    friend std::ostream& operator<<(std::ostream& os, const Card& card);
};
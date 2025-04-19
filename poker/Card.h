#pragma once    
#include "CardTypes.h"

class Card {
private:
    Rank rank;
    Suit suit;
public:
    Card(Rank r, Suit s);
    Rank getRank() const;
    Suit getSuit() const;
};
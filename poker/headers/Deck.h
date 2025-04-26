#ifndef __Deck__
#define __Deck__

#include <vector>
#include "Card.h"
#include <iostream>

class Deck {
private:
    std::vector<Card> cards;
public:
    Deck();
    void shuffle(); 
    Card dealCard();
    std::vector<Card> dealCards(int count);
    bool isEmpty() const;
    int getNumberOfCards() const;
    friend std::ostream& operator<< (std::ostream&os, const Deck& cards);
};

#endif
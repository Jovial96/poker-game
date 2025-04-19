#include <vector>
#include "Card.h"

class Player {
private:
    std::vector<Card> hand;
public:
    void receiveCard(const Card& card);
    void showHand() const;
    void clearHand();
};
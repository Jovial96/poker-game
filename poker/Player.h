#include <vector>
#include <string>
#include "Card.h"

class Player {
private:
    std::vector<Card> hand;
    std::string name;
public:
    Player(const std::string& name);
    void receiveCard(const Card& card);
    void showHand() const;
    void clearHand();
};
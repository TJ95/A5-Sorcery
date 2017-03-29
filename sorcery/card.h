#ifndef _CARD_H_
#define _CARD_H_
#include "cardtype.h"

#include <string>

class Card {
    int cost;
    std::string name;
public:
    Card(int c, std::string n, std::string t);
    int getCost();
    string getName();
    virtual CardType getType();
    virtual ~Card() = 0;
};

#endif /* card_hpp */

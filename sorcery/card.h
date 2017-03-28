#ifndef card_hpp
#define card_hpp

#include <string>

class Card {
    int cost;
    std::string name;
    std::string type;
public:
    Card(int c, std::string n, std::string t);
    virtual ~Card() = 0;
};

#endif /* card_hpp */

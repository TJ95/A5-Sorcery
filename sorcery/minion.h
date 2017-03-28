#ifndef minion_hpp
#define minion_hpp

#include <vector>
#include "card.hpp"

class Player;

class Minion: public Card {
    int attack;
    int defence;
    int actions;
public:
    void beat(Player P);
    void beat(Minion m);
    void die();
    void getATK();
};

#endif /* minion_hpp */

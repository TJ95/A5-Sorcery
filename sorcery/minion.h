#ifndef minion_hpp
#define minion_hpp

#include <vector>
#include "card.hpp"
#include "player.hpp"

class Minion: public Card {
    int attack;
    int defence;
    int actions;
public:
    virtual ~Minion() = 0;
    void beat(Player P);
    void beat(Minion* m);
    void die(Player P);
    int getATK();
    void modifySTAT(int a, int d);
};

#endif /* minion_hpp */

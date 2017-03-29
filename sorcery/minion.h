#ifndef _MINION_H_
#define _MINION_H_

#include <vector>
#include "card.h"
#include "player.h"
#include "cardtype.h"
class Player;
class Minion: public Card {
    int attack;
    int defence;
    int actions;
public:
    virtual ~Minion() = 0;
    void attack(Player *P);
    void attack(Minion* m);
    void die(Player P);
    int getATK();
    int getDEF();
    void setATK(int a);
    void setDEF(int d);
    void modifySTAT(int a, int d);
    CardType getType();
};

#endif /* minion_hpp */

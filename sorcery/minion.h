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
    int maxDef;
    int actions;
public:
    virtual ~Minion() = 0;
    virtual void attack(Player *P);
    virtual void attack(shared_ptr<Minion> m);
    virtual void die(Player *P);
    virtual void setActions(int act);
    virtual int getActions();
    virtual int getATK();
    virtual int getDEF();
    virtual int getMaxDef();
    virtual void setATK(int a);
    virtual void setDEF(int d); // this changes max def
    virtual void modifySTAT(int a, int d); // this adds def up to its max
    virtual CardType getType();
};

#endif /* minion_hpp */

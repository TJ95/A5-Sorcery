#ifndef _MINION_H_
#define _MINION_H_

#include <vector>
#include "card.h"
#include "player.h"
#include "cardtype.h"
class Player;
class Minion: public Card {
    double attk;
    double defence;
    double maxDef;
    int abilityCost;
    int actions;
public:
    virtual ~Minion() = 0;
    virtual void attack(Player *P);
    virtual void attack(std::shared_ptr<Minion> m);
    virtual void die(Player *P);
    virtual void setActions(int act);
    virtual int getActions();
    virtual double getAttack();
    virtual double getDEF();
    virtual int getMaxDef();
    virtual int getAbilityCost();
    virtual void setATK(int a);
    virtual void setDEF(int d); // this changes max def
    virtual void modifySTAT(double a, double d); // this adds def up to its max
    virtual CardType getType();
    virtual void useActiveAbility(std::shared_ptr<Card> c);
    virtual void useTriggerAbility(std::shared_ptr<Card> c);
};

#endif /* minion_hpp */

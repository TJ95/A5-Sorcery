#ifndef _MINION_H_
#define _MINION_H_

#include <vector>
#include <map>
#include "card.h"
#include "cardtype.h"
#include "ability.h"
#include "player.h"
#include <memory>

class Minion: public Card {
protected:
    double attk = 0;
    double defence= 0;
    int maxDef = 0;
    int actions = 0;
    std::vector<Ability> actAb;
    std::map<std::string,std::vector<Ability>> trigAb;

public:
	Minion(Player *owner, Player *opp);
    virtual ~Minion() = 0;
    virtual void attack(Player *P);
    virtual void attack(std::shared_ptr<Minion> m);
    virtual void setActions(int act);
    virtual int getActions();
    virtual double getAttack();
    virtual double getDEF();
    virtual int getMaxDef();
    virtual int getAC(int i);
    virtual void setATK(int a);
    virtual void setDEF(int d); // this changes max def
    virtual void modifySTAT(double a, double d); // this adds def up to its max
    virtual CardType getType();
    virtual void useActiveAbility(int i,std::shared_ptr<Minion> target=nullptr);
    virtual void useTriggerAbility(std::shared_ptr<Minion> c,std::string trigger);
    virtual void useTriggerAbility(std::string trigger);
    virtual std::map<std::string,std::vector<Ability>> getTrigger();
    virtual std::vector<Ability> getActive();

};

#endif /* minion_hpp */

#ifndef _RITUAL_H_
#define _RITUAL_H_
#include "card.h"
#include <string>
class Player;
class Ritual: public Card{
protected:
	int effectCost;
	int charge;
	std::string desp;
	virtual void init();
public:
	Ritual(Player *owner, Player *opp):Card(owner,opp){};
    int getEffectCost(){return effectCost;}
    int getCharge(){return charge;}
    void setCharge(int ch){charge=ch;}
	virtual void cast(std::string trigger){}
	virtual void cast(std::string trigger,std::shared_ptr<Minion> m){}
};

#endif

#ifndef _ABILITY_H_
#define _ABILITY_H_
#include "cardtype.h"
#include "card.h"
#include <string>

class Minion;
class Ability:public Card{
protected:
	std::string desp;
	int cost;
public:
	int getCost();
	Ability();
	std::string getDesp();
	CardType getType();
    virtual void cast(std::shared_ptr<Minion> m);

};
#endif

#ifndef _ABILITY_H_
#define _ABILITY_H_
#include "cardtype.h"
class Card;
class Minion;
class Ability:public Card{
protected:
	std::string desp;
	int cost;
public:
	int getCost();
	Ability();
	std::string getDesc();
	CardType getType();
	virtual void cast(Card *c);

};
#endif
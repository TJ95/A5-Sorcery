#ifndef _ABILITY_H_
#define _ABILITY_H_
#include "cardtype.h"
class Card;
class Ability:public Card{
	std::string descrip;
public:
	GainStat(std::string desp);
	std::string getDesc();
	CardType getType();
	virtual void cast(Card *c);

};
#endif
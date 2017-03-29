#ifndef _ABILITY_H_
#define _ABILITY_H_
#include "cardtype.h"
class Card;
class Ability:public Card{
public:
	CardType getType();
	virtual void cast(Card *c);

};
#endif
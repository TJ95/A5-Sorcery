#ifndef _SPELL_H_
#define _SPELL_H_
#include "card.h"
class Minion;
class Ritual;
class Spell: public Card{
protected:
	std::string desp;
	virtual void init(){};
public:
	Spell(Player *own,Player *pp);	
	virtual void cast(int i,std::shared_ptr<Minion> m){};
	virtual void cast(std::shared_ptr<Ritual> m){};
	virtual void cast();
};
Spell::Spell(Player *own,Player *opp){
	this->owner=own;
	this->opp=opp;
	init();
}



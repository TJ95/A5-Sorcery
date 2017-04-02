#include "spell.h"
#include "minion.h"
#include "cardtype.h"

class Banish:public Spell{
	void init()override;
	public:
		Banish(Player *own,Player *opp):Spell(own,opp){init()};
		void cast(std::shared_ptr<Minion> m)override;
		void cast(std::shared_ptr<Ritual> r)override;
};

class Unsummon:public Spell{
	void init()override;
	public:
		Unsummon(Player *own,Player *opp):Spell(own,opp){init()};
		void cast(std::shared_ptr<Minion> m)override;
};

void Banish::init(){
	name = "Banish";
	desp = "Destroy target minion or ritual"
	cost=2;
}

void Banish::cast(std::shared_ptr<Minion> m){
	int hp = m->getMaxDef();
	m->setDef(-hp);
}
//TODO
void Banish::cast(std::shared_ptr<Ritual> r){
	r->setCharge(0);
}
void Unsummon::init(){
	name="Unsummon";
	cost=1;
	desp="Return target minion to its owner's hand";
}

void Unsummon::cast(std::shared_ptr<Minion> m){
	std::shared_ptr<Minion> temp;
	while(m->getType()!=CardType::Minion){
		temp=std::move(m->getMinion());
	}
	if(temp->getDEF()<1){
		temp.setDEF(1);
	}
	if(temp->getAttack()<1){
		temp.setATK(1);
	}
	temp->getOwner->takeback(temp);
}
#include "spell.h"
#include "minion.h"
#include "cardtype.h"
#include "specificability.h"
#include "ritual.h"

class Banish:public Spell{
	void init()override;
	public:
		Banish(Player *own,Player *opp):Spell(own,opp){init();};
		void cast(int i,std::shared_ptr<Minion> m)override;
		void cast(std::shared_ptr<Ritual> r)override;
};

class Unsummon:public Spell{
	void init()override;
	public:
    Unsummon(Player *own,Player *opp):Spell(own,opp){init();};
		void cast(int i, std::shared_ptr<Minion> m) override;
};

class Recharge:public Spell{
	void init()override;
	public:
    Recharge(Player *own,Player *opp):Spell(own,opp){init();};
		void cast()override;
};

class Disenchant:public Spell{
	void init()override;
	public:
    Disenchant(Player *own,Player *opp):Spell(own,opp){init();};
		void cast(int i,std::shared_ptr<Minion> m )override;
};

class RaiseDead:public Spell{
void init()override;
	public:
    RaiseDead(Player *own,Player *opp):Spell(own,opp){init();};
		void cast()override;
};

class Blizzard:public Spell{
void init()override;
	public:
    Blizzard(Player *own,Player *opp):Spell(own,opp){init();};
		void cast()override;
};

void Banish::init(){
	name = "Banish";
	desp = "Destroy target minion or ritual";
	cost=2;
}

void Banish::cast(int i,std::shared_ptr<Minion> m){
	int hp = m->getMaxDef();
	m->setDEF(-hp);
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

void Unsummon::cast(int i,std::shared_ptr<Minion> m){
	m->getOwner()->takeback(i);
}

void Recharge::init(){
	name="Recharge";
	cost= 1;
	desp="Your ritual gains 3 charges";
}
void Recharge::cast(){
	std::shared_ptr<Ritual> r = owner->getR();
	if(r!=nullptr){
		//TODO
	}
}

void Disenchant::init(){
	cost=1;
	name="Disenchant";
	desp="Destroy the top enchantment on target minion";
}
void Disenchant::cast(int i,std::shared_ptr<Minion> m){
    if(m->getType()==CardType::Enchantment){
		m=m->getMinion();
	}
}

void RaiseDead::init(){
	cost=1;
	name="Raise Dead";
	desp="Resurrect the top minion in your graveyard and set its defence to 1";
}

void RaiseDead::cast(){
	owner->rez(opp);
}

void Blizzard::init(){
	cost= 3;
	name="Blizzard";
	desp="Deal 2 damage to all minions";
}

void Blizzard::cast(){
	AoE a(owner,opp,"",0,2);
	a.cast();
}


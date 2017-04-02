#include "enchantment.h"
#include "card.h"
#include "player.h"

class GiantStrength: public Enchantment{
protected:
void init() override;
	public:
    GiantStrength(Player *owner, Player *opp):Enchantment(owner,opp){init();};
    double getAttack()override;
    double getDEF()override;
    int getMaxDef()override;

};

class Enrage:public Enchantment{
	protected:
void init() override;
public:
	Enrage(Player *owner, Player *opp):Enchantment(owner,opp){init();};
	double getDEF() override;
	double getAttack() override;
	int getMaxDef() override;
	void modifySTAT(double d, double a) override;
};

class Haste: public Enchantment{
	protected:
void init() override;
public:
	Haste(Player *owner, Player *opp):Enchantment(owner,opp){init();};
	int getActions() override;

};

class MagicFatigue:public Enchantment{
	protected:
void init() override;
public:
	MagicFatigue(Player *owner, Player *opp):Enchantment(owner,opp){init();};
	int getAC(int i) override;
};

class Silence:public Enchantment{
	protected:
void init() override;
public:
	Silence(Player *owner, Player *opp):Enchantment(owner,opp){init();}
	void useActiveAbility(int i, std::shared_ptr<Minion> mi) override;

};
	double GiantStrength::getAttack(){
		return m->getAttack()+2;
	}

	double GiantStrength::getDEF(){
		return m->getDEF()+2;
	}

	int GiantStrength::getMaxDef(){
		return m->getMaxDef()+2;
	}

	int Haste::getActions(){
		return m->getActions()+1;
	}

	double Enrage::getDEF(){
		return m->getDEF()*2;
	}

	double Enrage::getAttack(){
		return m->getAttack()*2;
	}

	int Enrage::getMaxDef(){
		return m->getMaxDef()*2;
	}

	void Enrage::modifySTAT(double d, double a){
		m->modifySTAT(d/2,a/2);
	}

	int MagicFatigue::getAC(int i){
		return m->getAC(i)+2;
	}
	void Silence::useActiveAbility(int i,std::shared_ptr<Minion> c){
		std::cout<<"this minion cant use abilities"<<std::endl;
	}

	void GiantStrength::init(){
		cost=1;
		name="Giant Strength";
		desp="";
		attkMod="+2";
		defMod="+2";

	}

	void Enrage::init(){
		cost=2;
		name="Enrage";
		desp="";
		attkMod="*2";
		defMod="*2";
	}

	void Haste::init(){
		cost=1;
		name="Haste";
		desp="Enchanted minion gains +1 action each turn";
	}
	void MagicFatigue::init(){
		cost=0;
		name="Magic Fatigue";
		desp="Enchanted minion's activated ability costs 2 more";
	}
	void Silence::init(){
		cost=1;
		name="Silence";
		desp="Enchanted minion cannot use abilities";
	}
	
	


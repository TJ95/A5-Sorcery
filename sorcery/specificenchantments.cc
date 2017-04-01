#include "enchantment.h"
#include "card.h"
#include "player.h"

class GiantStrength: public Enchantment{

	public:
    double getAttack()override;
    double getDEF()override;
    int getMaxDef()override;

};

class Enrage:public Enchantment{
public:
	double getDEF() override;
	double getAttack() override;
	double getMaxDef() override;
	void modifySTAT(int d, int a) override;
};
class Haste: public Enchantment{
public:
	int getActions() override;

};

class MagicFatigue:public Enchantment{
public:
	int getAbilityCost() override;
};

class Silence:public Enchantment{
public:
	void useActiveAbility(std::shared_ptr<Card> c) override;

};

namespace Card::Minion::Enchantment{
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

	void Enrage::modifySTAT(int d, int a){
		m->modifySTAT(d/2,a/2);
	}

	int MagicFatigue::getAbilityCost(){
		return m->getAbilityCost()+2;
	}
	void Silence::useActiveAbility(std::shared_ptr<Card> c){
		std::cout<<"this minion cant use abilities"<<std::endl;
	}

}
	
	


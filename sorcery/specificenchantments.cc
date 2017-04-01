#include "enchantment.h"
#include "card.h"
class GiantStrength: public Enchantment{

	public:
    int getATK()override;
    int getDEF()override;
    int getMaxDef()override;

};

class Enrage:public Enchantment{
public:
	int getDEF() override;
	int getATK() override;
	int getMaxDef() override;
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
	void useActiveAbility(shared_ptr<Card> c) override;

};

namespace Card::Minion::Enchantment{
	int GiantStrength::getATK(){
		return m->getATK+2;
	}

	int GiantStrength::getDEF(){
		return m->getDEF+2;
	}

	int GiantStrength::getMaxDef(){
		return m->getMaxDef+2;
	}

	int Haste::getActions(){
		return m->getActions+1;
	}

	double Enrage::getDEF(){
		return m->getDEF()*2;
	}

	double Enrage::getATK(){
		return m->getATK()*2;
	}

	double Enrage::getMaxDef(){
		return m->getMaxDef()*2;
	}

	void Enrage::modifySTAT(int d, int a){
		m->modifySTAT(d/2,a/2);
	}

	int MagicFatigue::getAbilityCost(){
		return m->getAbilityCost()+2;
	}
	void Silence::useActiveAbility(shared_ptr<Card> c){
		std::cout<<"this minion cant use abilities"<<std::endl;
	}

}
	
	


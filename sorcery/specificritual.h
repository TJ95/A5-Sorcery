#ifndef _SPECIFICRITUAL_H_
#define _SPECIFICRITUAL_H_
#include "ritual.h"
#include <string>
#include "const.h"
#include "player.h"
#include "minion.h"
class DarkRitual:public Ritual{
	protected:
		void init() override;
	public:
    DarkRitual(Player *owner, Player *opp):Ritual(owner,opp){init();}
		void cast(std::string trigger) override;
};

class AuraOfPower:public Ritual{
	protected:
		void init() override;
	public:
    AuraOfPower(Player *owner, Player *opp):Ritual(owner,opp){init();}
		void cast(std::string trigger,std::shared_ptr<Minion> m) override;
};

class Standstill:public Ritual{
	protected:
		void init() override;
	public:
    Standstill(Player *owner, Player *opp):Ritual(owner,opp){init();}
		void cast(std::string trigger,std::shared_ptr<Minion> m) override;
};

void DarkRitual::init(){
	name="Dark Ritual";
	cost = 0;
	effectCost=1;
	charge=5;
	desp="At the start of your turn, gain 1 magic";
}
void DarkRitual::cast(std::string trigger){
	if(trigger==SoT&&charge>0){
		owner->CurMagicModify(1);
		charge--;
	}
}

void AuraOfPower::init(){
	name="Aura of Power";
	cost = 1;
	effectCost=1;
	charge=4;
	desp="Whenever a minion enter a play under your control, it gains +1/+1";
}

void AuraOfPower::cast(std::string trigger,std::shared_ptr<Minion> m){
	if(trigger==M_in&&charge>0){
		charge--;
		m->setATK(m->getAttack()+1);
		m->setDEF(m->getDEF()+1);
	}
}

void Standstill::init(){
	name="Standstill";
	cost = 3;
	effectCost=3;
	charge=4;
	desp="Whenever a minion enter a play, destroy it";
}

void Standstill::cast(std::string trigger,std::shared_ptr<Minion> m){
	if(trigger==M_in&&charge>0){
		charge-=2;
		m->modifySTAT(0,-m->getDEF());
	}
}

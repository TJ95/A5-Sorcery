#ifndef _SPECIFICABILITY_H_
#define _SPECIFICABILITY_H_
#include "card.h"
#include "player.h"
#include "const.h"

class GainStat: public Ability{
	int DFgain;
	int ATTKgain;
	Minion *host;
	public:
		GainStat(Player *own,std::string desp,int DFgain, int ATTKgain,int cost,Minion *m);
		void cast(std::shared_ptr<Minion> m);
		void cast();
};

class AoE: public Ability{
	int attk;
	public:
		AoE(Player *own, Player *opp,std::string desp,int cost,int attk);
		void cast(std::shared_ptr<Minion> m);
};

class AoEHealing: public Ability{
	int gain;
	public:
		AoEHealing(Player *own,std::string desp,int gain,int cost);
		void cast(std::shared_ptr<Minion> m);
};

class SingleDamage: public Ability{
	int attk;
	public:
		SingleDamage(std::string desp,int attk,int cost);
		void cast(std::shared_ptr<Minion> *m);
};

class Summon: public Ability{
	std::shared_ptr<Minion> m;
	int num;
	public:
		Summon(Player* p,std::string desp, std::shared_ptr<Minion> m,int num);
		void cast(std::shared_ptr<Minion> m);
};

	GainStat::GainStat(Player *own,std::string desp,int DFgain, int ATTKgain,int cost,Minion *m){
		this->owner=own;
		this->desp=desp;
		this->DFgain=DFgain;
		this->ATTKgain=ATTKgain;
		this->cost=cost;
		host=m;
	}

	void GainStat::cast(std::shared_ptr<Minion> m){
			m->modifySTAT(DFgain,ATTKgain);
	}

	void GainStat::cast(){
			host->modifySTAT(DFgain,ATTKgain);
	}

	AoE::AoE(Player *own, Player *opp,std::string desp,int cost,int attk){
		this->owner=own;
		this->opp=opp;
		this->desp=desp;
		this->attk=attk;
		this->cost=cost;
	}
	void AoE::cast(std::shared_ptr<Minion> mi =nullptr){
		if(opp!=nullptr){
			int pop = opp->getPop();
			for(int i = 0; i <pop;i++){
				auto m = opp->getBoard(i);
				m->modifySTAT(0,-attk);
			}
		}
		if(owner!=nullptr){
			int pop = owner->getPop();
			for(int i = 0; i <pop;i++){
				auto m = own->getBoard(i);
				m->modifySTAT(0,-attk);
			}
		}
	}

	AoEHealing::AoEHealing(Player *own,std::string desp,int gain,int cost){
		this->owner=own;
		this->desp=desp;
		this->gain=gain;
		this->cost=cost;
	}
	void AoEHealing::cast(std::shared_ptr<Minion> mi= nullptr){
		int pop = owner->getPop();
		for(int i = 0; i <pop;i++){
			auto m = owner->getBoard(i);
			m->modifyStat(gain,0);
		}
	}

	SingleDamage::SingleDamage(std::string desp,int attk,int cost){
		this->desp=desp;
		this->attk=attk;
		this->cost=cost;
	}

	void SingleDamage::cast(std::shared_ptr<Minion> m){
		m->modifyStat(0,-attk);
	}

	Summon::Summon(Player *own,std::string desp, std::shared_ptr<Minion> m,int num){
		this->m=m;
		this->desp=desp;
		owner=own;
		this->num=num;
	}

	void Summon::cast(std::shared_ptr<Minion> mi =nullptr){
		for(int i = 0; i <num i++){
			std::shared_ptr<Minion> o = std::make_shared<Event>(*m);
			owner->altSummon(o);
		}		
	}
#endif
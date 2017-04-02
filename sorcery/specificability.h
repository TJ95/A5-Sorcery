#ifndef _SPECIFICABILITY_H_
#define _SPECIFICABILITY_H_
#include "card.h"
#include "const.h"

class GainStat: public Ability{
	public:
		GainStat(std::string desp):Ability(desp){};
		void cast(std::shared_ptr<Minion> *m,int DFgain, int ATTKgain);
};

class AoE: public Ability{
	public:
		AoE(std::string desp):Ability(desp){};
		void cast(int attk);
		
};

class AoEHealing: public Ability{
	public:
		AoEHealing(std::string desp):Ability(desp){};
		void cast(int gain);
};

class SingleDamage: public Ability{
	public:
		SingleDamage(std::string desp):Ability(desp){};
		void cast(std::shared_ptr<Minion> *m,int attk);
};

class Summon: public Ability{
	public:
		GainStat(std::string desp):Ability(desp){};
		void cast(shared_ptr<Minion> m);
};
namespace Card::Ability{
	void GainStat::cast(std::shared_ptr<Minion> *m,int DFgain, int ATTKgain){
			m->modifyStat(DFgain,ATTKgain);
	}
	void AoE::cast(int attk){
		int pop = opp->getPop();
		for(int i = 0; i <pop;i++){
			auto m = opp->getBoard(i);
			m->modifyStat(0,-attk);
		}
	}
	void AoEHealing::cast(int attk){
		int pop = owner->getPop();
		for(int i = 0; i <pop;i++){
			auto m = owner->getBoard(i);
			m->modifyStat(0,-attk);
		}
	}
	void SingleDamage::cast(std::shared_ptr<Minion> m,int attk){
		m->modifyStat(0,-attk);
	}
	void Summon::cast(std::shared_ptr<Minion> m){
		if(owner->getPop>=maxPop){
			//throw error
		}
		else{
			owner->altSummon(m);
		}
	}
}

#endif
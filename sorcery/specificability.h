#ifndef _SPECIFICABILITY_H_
#define _SPECIFICABILITY_H_
#include "card.h"

class GainStat: public Ability{
public:
	void cast(Card *c,int gain);
};
namespace Card::Ability{
	void GainStat::cast(Card *c,int DFgain, int ATTKgain){
		if(c.getType()==Minion){
			Minion *m = c;
			m.modifyStat(DFgain,ATTKgain);
		}

	}
}

#endif
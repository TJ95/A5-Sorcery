#include "enchantment.h"
class GiantStrength: public Enchantment{

	public:
    int getATK();
    int getDEF();
    int getMaxDef();
    void setATK(int a);
    void setDEF(int d);
};
class Haste: public Enchantment{
public:
	int getActions() override;

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
}
	
	


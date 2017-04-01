#ifndef _ENCHANTMENT_H_
#define _ENCHANTMENT_H_
#include "minion.h"
#include "cardtype.h"

class Minion;
class Enchantment: Public Minion{
	std::shared_ptr<Minion> m;
	public:
	Enchantment(std::shared_ptr<Minion> m);
	void attack(Player *P) override;
    void attack(Minion* m) override;
    virtual void die(Player P);
    virtual int getATK();
    virtual int getDEF();
    virtual int getMaxDef();
    virtual int getActions();
    virtual void useActiveAbility(shared_ptr<Card> c);
    virtual void setActions(int act);
    void setATK(int a) override;
    void setDEF(int d) override;
    CardType getType() override;
};
#endif

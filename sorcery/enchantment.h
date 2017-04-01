#ifndef _ENCHANTMENT_H_
#define _ENCHANTMENT_H_
#include "minion.h"
#include "cardtype.h"

class Minion;
class Enchantment: public Minion{
	std::shared_ptr<Minion> m;
	public:
	Enchantment(std::shared_ptr<Minion> m);
	void attack(Player *P) override;
    void attack(std::shared_ptr<Minion> m) override;
    virtual void die(Player *P);
    virtual double getAttack();
    virtual double getDEF();
    int getMaxDef();
    virtual int getActions();
    virtual void useActiveAbility(std::shared_ptr<Card> c);
    virtual void setActions(int act);
    void setATK(int a) override;
    void setDEF(int d) override;
    CardType getType() override;
};
#endif

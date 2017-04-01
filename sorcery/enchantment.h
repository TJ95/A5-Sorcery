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
    virtual double getAttack() override;
    virtual double getDEF() override;
    int getMaxDef() override;
    virtual int getActions() override;
    virtual void useActiveAbility(std::shared_ptr<Card> c) override;
    void setATK(int a) override;
    void setDEF(int d) override;
    virtual void modifySTAT(double a, double d) override;
    CardType getType() override;
};
#endif

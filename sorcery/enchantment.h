#ifndef _ENCHANTMENT_H_
#define _ENCHANTMENT_H_
#include "minion.h"
#include "cardtype.h"
#include <memory>


class Minion;
class Enchantment: public Minion{
protected:
	std::shared_ptr<Minion> m;
    virtual void init();
    std::string desp;
    std::string attkMod="";
    std::string defMod ="";
	public:
	Enchantment(Player *owner, Player *opp);
    void setMinion(std::shared_ptr<Minion>m);
	void attack(Player *P) override;
    void attack(std::shared_ptr<Minion> m) override;
    virtual double getAttack() override;
    virtual double getDEF() override;
    int getMaxDef() override;
    virtual int getActions() override;
    void setATK(int a) override;
    void setDEF(int d) override;
    virtual void modifySTAT(double a, double d) override;
    CardType getType() override;
    void setActions(int act)override;
    int getAC(int i) override;
    void useActiveAbility(int i,std::shared_ptr<Minion> target=nullptr)override;
    void useTriggerAbility(std::shared_ptr<Minion> c,std::string trigger)override;
    void useTriggerAbility(std::string trigger) override;
    std::map<std::string,std::vector<Ability>> getTrigger() override;
    std::vector<Ability> getActive() override;
    std::string getDesp();
    std::string getAttkMod();
    std::string getDefMod();
    std::shared_ptr<Minion> getMinion();
};
#endif

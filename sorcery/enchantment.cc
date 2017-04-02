#include "enchantment.h"
#include "cardtype.h"
using namespace std;
Enchantment::Enchantment(Player *owner, Player *op):Minion(owner,op){
	init();
}
void Enchantment::setMinion(std::shared_ptr<Minion> m){
	this->m=m;
}
void Enchantment::init(){}
CardType Enchantment::getType(){
	return CardType::Enchantment;
}

void Enchantment::attack(Player *p){
	int attk = (int)m->getAttack();
	p->LifeModify(-attk);
}
void Enchantment::attack(std::shared_ptr<Minion> minion){
	int attk = (int)m->getAttack();
	minion->modifySTAT(-attk,0);
	m->modifySTAT(-minion->getAttack(),0);
}
void Enchantment::modifySTAT(double a, double d){
	m->modifySTAT(a,d);
}
void Enchantment::setATK(int attk){
	m->setATK(attk);
}
void Enchantment::setDEF(int attk){
	m->setATK(attk);
}
double Enchantment::getAttack(){
	return m->getAttack();
}
int Enchantment::getActions(){
	return m->getActions();
}
void Enchantment::setActions(int actions){
	m->setActions(actions);
}
double Enchantment::getDEF(){
	return m->getDEF();
}
int Enchantment::getMaxDef(){
	return m->getMaxDef();
}

int Enchantment::getAC(int i){
	return m->getAC(i);
}

void Enchantment::useActiveAbility(int i,std::shared_ptr<Minion> target){
	m->useActiveAbility(i,target);
}

void Enchantment::useTriggerAbility(std::shared_ptr<Minion> c,std::string trigger){
	m->useTriggerAbility(c,trigger);
}

void Enchantment::useTriggerAbility(std::string trigger){
	m->useTriggerAbility(trigger);
}

std::map<std::string,std::vector<Ability>> Enchantment::getTrigger(){
	return m->getTrigger();
}

std::vector<Ability> Enchantment::getActive(){
	return m->getActive();
}

std::string Enchantment::getDesp(){
	return desp;
}
std::string Enchantment::getAttkMod(){
	return attkMod;
}

std::string Enchantment::getDefMod(){
	return defMod;
}

std::shared_ptr<Minion> Enchantment::getMinion(){
	return m;
}

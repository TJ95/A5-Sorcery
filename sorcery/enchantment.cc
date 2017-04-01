#include "enchantment.h"
#include "cardtype.h"
using namespace std;
CardType Enchantment::getType(){
	return CardType::Enchantment;
}
void Enchantment::attack(Player *p){
	double attk = m->getAttack();
	p->LifeModify(-attk);
}
void Enchantment::attack(shared_ptr<Minion> minion){
	double attk = m->getAttack();
	minion->modifySTAT(-attk,0);
	m->modifySTAT(-minion->getAttack(),0);
}
void Enchantment::setATK(int attk){
	m->setATK(attk);
}
void Enchantment::setDEF(int attk){
	m->setATK(attk);
}
int Enchantment::getActions(){
	return m->getActions();
}
void Enchantment::setActions(int actions){
	return m->setActions(actions);
}
void useActiveAbility(shared_ptr<Card> c);

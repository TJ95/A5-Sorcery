#include "minion.h"
using namespace std;

Minion::~Minion() {}

Minion::Minion(Player *owner,Player *opp):Card(owner,opp){
	this->owner=owner;
	this->opp=opp;
}

void Minion::attack(Player *P) {
	int atk = getAttack();
    P->LifeModify(-atk);
}

void Minion::attack(shared_ptr<Minion> m) {
    m->modifySTAT (0, -getAttack());
    this->modifySTAT(0,-(m->getAttack()));
}

double Minion::getAttack() {
    return attk;
}

double Minion::getDEF() {
    return defence;
}

void Minion::setDEF(int def) {
    defence = (double)def;
    maxDef = def;
}

int Minion::getMaxDef(){
	return maxDef;
}

void Minion::setATK(int attk) {
    attk = (double)attk;
}

void Minion::modifySTAT(double a, double d) {
    attk += a;
    defence = (defence+d>getMaxDef())? maxDef: defence+d;
}

void Minion::setActions(int a ){
	actions = a;
}

int Minion::getActions(){
	return actions;
}

int Minion::getAC(int i){
	return actAb[i].getCost();
}

CardType Minion::getType(){
	return CardType::Minion;
}

 void Minion::useActiveAbility(int i,std::shared_ptr<Minion> c){
 	actAb[i].cast(c);
 }

 void Minion::useTriggerAbility(std::shared_ptr<Minion> c,string trigger){
 	std::vector<Ability> v = trigAb.find(trigger)->second;
 	for(Ability a:v ){
 		a.cast(c);
 	}
 }

 void Minion::useTriggerAbility(std::string trigger){
 	std::vector<Ability> v = trigAb.find(trigger)->second;
 	for(Ability a:v ){
 		a.cast(nullptr);
 	}
 }

std::map<string,std::vector<Ability>> Minion::getTrigger(){
	return trigAb;
}

std::vector<Ability> Minion::getActive(){
	return actAb;
}

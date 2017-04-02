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

void Minion::die() {
    owner->bury();
}

double Minion::getAttack() {
    return attk;
}

double Minion::getDEF() {
    return defence;
}

void Minion::setDEF(int def) {
    defence = def;
    maxDef = def;
}

int Minion::getMaxDef(){
	return maxDef;
}

void Minion::setATK(int attk) {
    attk = attk;
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

int Minion::getAbilityCost(){
	return abilityCost;
}

CardType Minion::getType(){
	return CardType::Minion;
}
std::string Minion::getTriggerDesc(){
	for(Ability a:trigAb){
		cout<<a.getDesc();
	};
}

std::string getActiveDesc(){
	for(Ability a:actAb){
		cout<<a.getDesc();
	};
}

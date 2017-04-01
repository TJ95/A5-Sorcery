#include "minion.hpp"

Minion::~Minion() {}

void Minion::attack(Player *P) {
	int attk = getAttack();
    P->LifeModify(-attk);
}

void Minion::attack(shared_ptr<Minion> m) {
    m->modifySTAT (0, -getAttack());
    this->modifySTAT(0,-(m->getAttack());
}

void Minion::die(Player P) {
    P.bury();
}

double Minion::getATK() {
    return attack;
}

double Minion::getDEF() {
    return defence;
}

void Minion::setDEF(int def) {
    defence = def;
    maxDef = def;
}

int getMaxDef(){
	return maxDef;
}

void Minion::setATK(int attk) {
    attack = attk;
}

void Minion::modifySTAT(double a, double d) {
    attack += a;
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

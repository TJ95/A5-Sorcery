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

int Minion::getATK() {
    return attack;
}

int Minion::getDEF() {
    return defence;
}

int Minion::setDEF(int def) {
    defence = def;
    maxDef = def;
}

int getMaxDef(){
	return maxDef;
}

int Minion::setATK(int attk) {
    attack = attk;
}

void Minion::modifySTAT(int a, int d) {
    attack += (defence+d>getATK())? maxDef: defence+d;
    defence = (defence+d>getMaxDef())? maxDef: defence+d;
}

void Minion::setActions(int a ){
	actions = a;
}

int Minion::getActions(){
	return actions;
}
CardType Minion::getType(){
	return CardType::Minion;
}

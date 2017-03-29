#include "minion.hpp"

Minion::~Minion() {}

void Minion::attack(Player P) {
    P.LifeModify(-attack);
}

void Minion::attack(Minion* m) {
    m->modifySTAT (0, -attack);
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
}

int Minion::setATK(int attk) {
    attack = attk;
}

void Minion::modifySTAT(int a, int d) {
    attack += a;
    defence += d;
}

CardType getType(){
	return CardType::Minion;
}

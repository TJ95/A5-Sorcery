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

void Minion::modifySTAT(int a, int d) {
    attack += a;
    defence += d;
}

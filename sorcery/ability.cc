#include "ability.h"
#include "cardtype.h"

Ability::Ability(){};

CardType Ability::getType(){
	return CardType::Ability;
}

std::string Ability::getDesp(){
	return desp;
}

int Ability::getCost(){
	return cost;
}
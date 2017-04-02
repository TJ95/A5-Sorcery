#include "ability.h"
#include "cardtype.h"

Ability::Ability(std::string desp):descrip(desp){};

CardType Ability::getType(){
	return CardType::Ability;
}

std::string Ability::getDesc(){
	return desp;
}
#include "card.h"

using namespace std;

Card::Card(int c, string n, string t)
: cost{c}, name{n}, type{t} {}

CardType Card::getType(){
	return CardType::Card;
}

int Card::getCost(){
	return cost;
}

string Card::getName(){
	return name;
}

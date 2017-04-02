#include "card.h"
using namespace std;

Card::Card(){

}

Card::Card(Player *owner, Player *opp)
: owner{owner}, opp{opp}{}

CardType Card::getType(){
	return CardType::Card;
}

int Card::getCost(){
	return cost;
}

string Card::getName(){
	return name;
}

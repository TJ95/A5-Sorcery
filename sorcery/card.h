#ifndef _CARD_H_
#define _CARD_H_
#include "cardtype.h"


#include <string>

class Player;
class Card {
	protected:
		Player *owner=nullptr;
	    Player *opp=nullptr;
    	int cost;
        std::string name;
	public:
		Card();
	    Card(Player *owner, Player *opp);
	    Player* getOwner();
	    int getCost();
	    std::string getName();
	    virtual CardType getType();
	    virtual ~Card() = 0;
};

#endif /* card_hpp */

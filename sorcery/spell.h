#ifndef spell_hpp
#define spell_hpp

#include "card.h"
#include "player.h"
#include <vector>

class Spell: public Card {
public:
    virtual void castSpell(Card c) = 0;
};


#endif /* spell_hpp */

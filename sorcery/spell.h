#ifndef spell_hpp
#define spell_hpp

#include "card.hpp"
#include "player.hpp"
#include <vector>

class Spell: public Card {
public:
    virtual void castSpell(Card c) = 0;
};


#endif /* spell_hpp */

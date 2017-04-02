#include "player.hpp"
#include "observer.hpp"
#include "subject.hpp"
#include "card.hpp"
#include "minion.hpp"
#include "cardtype.h"
#include "spell.hpp"
#include "enchantment.hpp"


using namespace std;
class Ritual;
//Player(std::string deckname); //ctor for Player

void Player::LifeModify(int n) {
    life += n;
}

void Player::MagicModify(int n) {
    magic += n;
}

void Player::CurMagicModify(int n) {
    current_magic += n;
}

void Player::CurMagicSet(int n) {
    current_magic = n;
}

//playing cards
void Player::play(int card, int targ, Player* p) {
    shared_ptr<Card> temp = Hand[card - 1];
    if (current_magic >= temp->getCost()) {
        if ((targ == -1)&&(!p)) { //no target
            if (temp->getType() == CardType::Spell) {
                dynamic_pointer_cast<shared_ptr<Spell>> (temp);
                temp->castSpell(this);
                CurMagicModify(-(temp->getCost())); //spell w/o target
                Graveyard.emplace_back(temp);
                Hand.erase(Hand.begin() + card - 1);
            } else if (temp->getType() == CardType::Minion) { //minion
                for (int i = 0; i < 4; i++) {
                    if (i == 4) {
                        cout << "board has no space" << endl;
                        break;
                    }
                    else if (!Board[i]) {
                        Board[i] = temp;
                        Hand.erase(Hand.begin() + card - 1);
                        CurMagicModify(-(temp->getCost()));
                        break;
                    }
                }
            } else if (temp->getType() == CardType::Ritual) { //ritual
                dynamic_pointer_cast<shared_ptr<Ritual>> (temp);
                if (!shrine) {
                    Graveyard.emplace_back(shrine);
                }
                CurMagicModify(-(temp->getCost()));
                shrine = temp;
                Hand.erase(Hand.begin() + card - 1);
            }
        } else if ((targ == -1)&&p) {
            dynamic_pointer_cast<shared_ptr<Spell>> (temp);
            temp->castSpell(this, p); //aoe spell
            CurMagicModify(-(temp->getCost()));
            Graveyard.emplace_back(temp);
            Hand.erase(Hand.begin() + card - 1);
            
        } else {
            if (temp->getType() == CardType::Spell) {
                dynamic_pointer_cast<shared_ptr<Spell>> (temp);
                temp->castSpell(p, targ); //spell w target
                CurMagicModify(-(temp->getCost()));
                Graveyard.emplace_back(temp);
                Hand.erase(Hand.begin() + card - 1);
            } else if (temp->getType() == CardType::Enchantment) {
                dynamic_pointer_cast<shared_ptr<Enchantment>> (temp);
                //????
            }
        }
    } else {
        cout << "not enough mana!" << endl;
    }
}

shared_ptr<Card> Player::getBoard (int slot) {
    if (slot != 6) {
        return Board[slot - 1];
    } else {
        return shrine;
    }
}

int Player::getPop() {
    int return_val = Board.size();
    if (Board[5]) return_val -= 1;
    return return_val;
}

void Player::altSummon(std::shared_ptr<Minion> m) {
    if (Board.size() == 5) {
        cout << "full" << endl;
    }else {
        for (int i = 0; i < 4; i++) {
            if (!Board[i])
                Board[i] = m;
        }
    }
}

void Player::draw(int time) {
    if (Hand.size() < 5) {
        for (int i = 0; i < time; i++) {
            Hand.emplace_back(Deck[0]);
            Deck.erase(Deck.begin());
        }
    }
}

void Player::discard(int i) {
    if (Hand.size() > 0) {
        Graveyard.emplace_back(Hand[i]);
        Hand.erase(Hand.begin()+i);
    }
}

void Player::bury() {
    if (Board.size() != 0) {
        for (int i = 0; i < Board.size(); i++) {
            if (Board[i]->getType() == CardType::Minion&&Board[i]->getDEF()<=0) {
                Graveyard.emplace_back(Board[i]);
                Board[i] = nullptr;
            }
        }
    }
}

void Player::forfeit() {
    life = 0;
}

void Player::inspect(int i) {
    if (!Board[i]) {
        cout << "please select a minion" << endl;
    } else {
        cout << "..";
    }
}

bool Player::isLost() {
    return !(life > 0);
}

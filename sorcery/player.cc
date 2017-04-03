#include "player.h"
#include "observer.h"
#include "subject.h"
#include "card.h"
#include "minion.h"
#include "cardtype.h"
#include "spell.h"
#include "enchantment.h"
#include "specificminion.cc"
#include "ritual.h"
#include "specificspell.cc"

using namespace std;
class Ritual;

Player::Player(string name)
: name{name}, life{20}, magic{3}, current_magic{3}, shrine{nullptr}
//Hand{vector<shared_ptr<Card>>}, Board{vector<shared_ptr<Minion>>},
//Deck{vector<shared_ptr<Card>>}, Graveyard{vector<shared_ptr<Minion>>} {}
{}

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

void Player::DeckSet(vector<shared_ptr<Card>> d) {
    Deck = d;
}

void Player::play(int card) {
    shared_ptr<Card> temp = Hand[card - 1];
    if (temp->getType() == CardType::Minion) {
        auto mm = make_shared<Minion>(*temp);
        for (int i = 0; i < 4; i++) {
            if (i == 4) {
                cout << "board has no space" << endl;
                break;
            }
            else if (!Board[i]) {
                Board[i] = mm;
                Hand.erase(Hand.begin() + card - 1);
                CurMagicModify(-(temp->getCost()));
                break;
            }
        }
    }
}

//playing cards
void Player::play(int card, int targ, Player* p) {
    shared_ptr<Card> temp = Hand[card - 1];
    if (current_magic >= temp->getCost()) {
        if ((targ == -1)&&(!p)) { //no target
            if (temp->getType() == CardType::Spell) {
                auto ss = make_shared<Spell>(*temp);
                ss->cast();
                CurMagicModify(-(temp->getCost())); //spell w/o target
                Hand.erase(Hand.begin() + card - 1);
            } else if (temp->getType() == CardType::Ritual) { //ritual
                if (!shrine) {
                    Graveyard.emplace_back(shrine);
                }
                CurMagicModify(-(temp->getCost()));
                shrine = make_shared<Ritual>(*temp);
                Hand.erase(Hand.begin() + card - 1);
            }
        } else if ((targ == -1)&&p) {
            auto ss = make_shared<Spell>(*temp);
            ss->cast(); //aoe spell
            CurMagicModify(-(temp->getCost()));
            Hand.erase(Hand.begin() + card - 1);
            
        } else {
            if (temp->getType() == CardType::Spell) {
                auto ss = make_shared<Spell>(*temp);
                if (targ != 6) {
                    ss->cast(targ, p->getBoard(targ)); //spell w target
                } else {
                    ss->cast(p->getR());
                }
                CurMagicModify(-(temp->getCost()));
                Hand.erase(Hand.begin() + card - 1);
            } else if (temp->getType() == CardType::Enchantment) {
                auto ee = make_shared<Enchantment>(*temp);
                ee->setMinion(p->getBoard(targ));
                p->getBoard(targ) = ee;
            }
        }
    } else {
        cout << "not enough mana!" << endl;
    }
}
//use!
void Player::use(int m, int targ, Player* p) {
    shared_ptr<Minion> temp = Board[m - 1];
    if (current_magic >= temp->getAC(0)) {
        if (targ == -1) {
            temp->useActiveAbility(0);
            CurMagicModify(-temp->getAC(0));
        } else {
            temp->useActiveAbility(0, p->getBoard(targ));
            CurMagicModify(-temp->getAC(0));
        }
    } else {
        cout << "not enough mana!" << endl;
    }
}

shared_ptr<Minion> Player::getBoard (int slot) {
        return Board[slot - 1];
}

shared_ptr<Ritual> Player::getR () {
    return shrine;
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

void Player::rez(Player* p) {
    if (Graveyard.size() == 0) {
        Hand.emplace_back(new RaiseDead(this, p));
        current_magic += 1;
    } else {
        shared_ptr<Minion> temp = *(Graveyard.rbegin());
        altSummon(temp);
        Graveyard.pop_back();
    }
}


void Player::trigger(Player *p, std::string s, int targ, int owner) {
    if (targ == -1) {
        for (int i = 0; i < 5; i++) {
            Board[i]->useTriggerAbility(s);
        }
    } else {
        Player* targ_owner = this;
        if (owner == 2) {
            targ_owner = p;
        }
        for (int i = 0; i < 5; i++) {
            Board[i]->useTriggerAbility(targ_owner->getBoard(targ), s);
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
                auto mp = make_shared<Card>(*(Board[i]));
                
                shared_ptr<Minion> temp;
                while(Board[i]->getType()!=CardType::Minion){
                    temp = move(Board[i]->getMinion());
                }
                if(temp->getDEF()<1){
                    temp->setDEF(1);
                }
                if(temp->getAttack()<1){
                    temp->setATK(1);
                }
                
                Graveyard.emplace_back(temp);
                Board[i] = nullptr;
            }
        }
    }
}

void Player::buryR() {
    if (shrine->getCharge() == 0) {
        auto mp = make_shared<Card>(*shrine);
        Graveyard.emplace_back(shrine);
        shrine = nullptr;
    }
}

void Player::takeback(int i) {
    if (Hand.size() == 5) {
        Graveyard.emplace_back(Board[i]);
        Board[i] = nullptr;
    } else {
        Hand.emplace_back(Board[i]);
        Board[i] = nullptr;
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

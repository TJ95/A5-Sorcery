#include "player.h"
#include "observer.h"
#include "subject.h"
#include "card.h"
#include "minion.h"
#include "cardtype.h"
#include "spell.h"
#include "enchantment.h"


using namespace std;
class Ritual;

Player::Player(string name)
: name{name}, life{20}, magic{3}, current_magic{3}, shrine{nullptr},
Hand{vector<shared_ptr<Card>>(5,nullptr)}, Board{vector<shared_ptr<Card>>(5, nullptr)},
Deck{vector<shared_ptr<Card>>(0, nullptr)}, Graveyard{vector<shared_ptr<Card>>(0,nullptr)} {}

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

shared_ptr<Minion> Player::getBoard (int slot) {
        return Board[slot - 1];
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

void Player::use(int m, int targ, Player* p) {
    if (targ == -1) {
        getBoard(m - 1)->useActiveAbility(0);
    } else {
        getBoard(m - 1)->useActiveAbility(0, p->getBoard(targ));
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

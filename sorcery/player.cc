#include "player.hpp"
#include "observer.hpp"
#include "subject.hpp"
#include "card.hpp"
#include "minion.hpp"


using namespace std;

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


void Player::play(int card) { //summon&place ritual
    shared_ptr<Card> temp = Hand[card - 1];
    if (current_magic >= temp->getCost()) {
        if (temp->getType() == Minion) {
            for (int i = 0; i < 5; i++) {
                if (i == 5) {
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
        } else if (temp->getType() == Ritual) {
            if (!Board[5]) {
                Graveyard.emplace_back(Board[5]);
                Board.erase(Board.begin() + 5);
            }
            CurMagicModify(-(temp->getCost()));
            Board[5] = temp;
            Hand.erase(Hand.begin() + card - 1);
        }
    } else {
        cout << "not enough mana!" << endl;
    }
}

void Player::play(int card, int targ, Player* p) { //spell&enchant
    shared_ptr<Card> temp = Hand[card - 1];
    if (current_magic >= temp->getCost()) {
        if (temp->getType() == Spell) {
            if ((targ == -1)&&(!p)) {
                temp->castSpell(this);
                CurMagicModify(-(temp->getCost()));
                
            } else if (targ == -1) {
                temp->castSpell(this, p);
            } else {
                temp->castSpell(p, card, targ);
            }
            Graveyard.emplace_back(temp);
            Hand.erase(Hand.begin() + card - 1);
        } else if (temp->getType() == Enchantment) {
            //target = make_shared<Card>(temp, target);
        }
    } else {
        cout << "not enough mana!" << endl;
    }
}

shared_ptr<Card> Player::getBoard (int slot) {
    return Board[slot];
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
        for (int i = 0; i < Board.size(); i++) {             //should be Minion's getDefence
            if (Board[i]->getType() == "Minion"&&Board[i]->getCost()<=0) {
                Graveyard.emplace_back(Board[i]);
                Board[i] = nullptr;
            } else if (Board[i]->getType()=="Ritual"&&Board[i]->getCost()==0) {
                Graveyard.emplace_back(Board[i]);
                Board[i] = nullptr;
            }
        }
    }
}

void Player::forfeit() {
    life = 0;
}

//void endTurn() {}

//void inspect(int i) {

//}

bool Player::isLost() {
    return !(life > 0);
}

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "player.h"
#include "card.h"
#include "specificminion.cc"
#include "specificenchantments.cc"
#include "specificritual.h"
#include "specificspell.cc"

using namespace std;

//deck_loader loads from a .deck file and returns a vector containing
//  the name of the cards in the deck
vector<shared_ptr<Card>> deck_loader(string deckname, Player* owner, Player* opp) {
    vector<shared_ptr<Card>> return_deck;
    string temp;
    ifstream ifs{deckname+".deck"};
    while (getline(ifs,temp)) {
        if (temp == "Air Element") {
            auto cp = make_shared<Card> ( new AirElemental(owner, opp) );
            return_deck.emplace_back(cp);
        } else if (temp == "Earth Element") {
            auto cp = make_shared<Card> ( new EarthElemental(owner, opp) );
            return_deck.emplace_back(cp);
        } else if (temp == "Bone Golem") {
            auto cp = make_shared<Card> ( new BoneGolem(owner, opp) );
            return_deck.emplace_back(cp);
        } else if (temp == "Potion Seller") {
            auto cp = make_shared<Card> ( new PotionSeller(owner, opp) );
            return_deck.emplace_back(cp);
        } else if (temp == "Fire Elemental") {
            auto cp = make_shared<Card> ( new FireElemental(owner, opp) );
            return_deck.emplace_back(cp);
        } else if (temp == "Novice Pyromancer") {
            auto cp = make_shared<Card> ( new NovicePyromancer(owner, opp) );
            return_deck.emplace_back(cp);
        } else if (temp == "Apprentice Summoner") {
            auto cp = make_shared<Card> ( new ApprenticeSummoner (owner, opp));
            return_deck.emplace_back(cp);
        } else if (temp == "Master Summoner") {
            auto cp = make_shared<Card> ( new MasterSummoner(owner, opp) );
            return_deck.emplace_back(cp);
        } else if (temp == "Banish") {
            auto cp = make_shared<Card> ( new Banish(owner, opp) );
            return_deck.emplace_back(cp);
        } else if (temp == "Unsummon") {
            auto cp = make_shared<Card> ( new Unsummon(owner, opp) );
            return_deck.emplace_back(cp);
        } else if (temp == "Disenchant") {
            auto cp = make_shared<Card> ( new Disenchant(owner, opp) );
            return_deck.emplace_back(cp);
        } else if (temp == "Raise Dead") {
            auto cp = make_shared<Card> ( new RaiseDead (owner, opp));
            return_deck.emplace_back(cp);
        } else if (temp == "Blizzard") {
            auto cp = make_shared<Card> ( new Blizzard (owner, opp));
            return_deck.emplace_back(cp);
        } else if (temp == "Giant Strength") {
            auto cp = make_shared<Card> ( new GiantStrength (owner, opp));
            return_deck.emplace_back(cp);
        } else if (temp == "Enrage") {
            auto cp = make_shared<Card> ( new Enrage (owner, opp));
        } else if (temp == "Haste") {
            auto cp = make_shared<Card> ( new Haste (owner, opp));
            return_deck.emplace_back(cp);
        } else if (temp == "Magic Fatigue") {
            auto cp = make_shared<Card> ( new MagicFatigue (owner, opp));
            return_deck.emplace_back(cp);
        } else if (temp == "Silence") {
            auto cp = make_shared<Card> ( new Silence (owner, opp));
            return_deck.emplace_back(cp);
        } else if (temp == "Dark Ritual") {
            auto cp = make_shared<Card> ( new DarkRitual (owner, opp));
            return_deck.emplace_back(cp);
        } else if (temp == "Aura of Power") {
            auto cp = make_shared<Card> ( new AuraOfPower (owner, opp));
            return_deck.emplace_back(cp);
        } else if (temp == "Standstill") {
            auto cp = make_shared<Card> ( new Standstill (owner, opp));
            return_deck.emplace_back(cp);
        } else {
            cout << "There is no such card as" << temp << "!" << endl;
        }
    }
    return return_deck;
}

int main(int argc, char* argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd, aux;
    int num, num2, num3;
    Player p1("player1");
    Player* pl1 = &p1;
    Player p2("player2");
    Player* pl2 = &p2;
    Player* activeP = pl1;
    Player* otherP = pl2;
    
    int turnno = 0;
    bool isTesting = false;
    vector<shared_ptr<Card>> deck1;
    vector<shared_ptr<Card>> deck2;
    ifstream inpt;
    
    //command line arguments
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            string s = argv[i];
            if (s == "-testing") {
                isTesting = true;
                cout << "testing mode actived"<<endl;
            }
            else if (s == "-deck1") {
                deck1 = deck_loader(argv[i+1], pl1, pl2);
                pl1->DeckSet(deck1);
                i++;
                cout << "deck1 loaded" << endl;
            }
            else if (s == "-deck2") {
                deck1 = deck_loader(argv[i+1], pl2, pl1);
                pl2->DeckSet(deck2);
                i++;
                cout << "deck2 loaded" << endl;
            }
            else if (s == "-init") {
                aux = argv[i+1];
                inpt = ifstream{aux};
                cout << "init" << endl;
            }
            else if (s == "graphics") {
                cout << "init" << endl;
            }
        }
    }
    
    //load the default deck for players if no deck is given
    if (deck1.size() == 0) deck1 = deck_loader("default", pl1, pl2);
    if (deck2.size() == 0) deck2 = deck_loader("default", pl2, pl1);
    p1.DeckSet(deck1);
    p2.DeckSet(deck2);
    
    p1.draw(5);
    p2.draw(5);
    
    try {
        while (true) {
            if (p1.isLost()||p2.isLost()) {
                if (p1.isLost()) {
                    cout << "p1 won" << endl;
                    break;
                } else {
                    cout << "p2 won" << endl;
                    break;
                }
            }
            if (!( inpt >> cmd )) {
                cin >> cmd;
            }
            
            if (cmd == "help") { //help message
                cout << "Commands:  help -- Display this message." << endl;
                cout << "           end -- End the current player’s turn." << endl;
                cout << "           quit -- End the game."<<endl;
                cout << "           attack minion other-minion -- Orders minion to attack other-minion." << endl;
                cout << "           attack minion -- Orders minion to attack the opponent." << endl;
                cout << "           play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
                cout << "           use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player. inspect minion -- View a minion’s card and all enchantments on that minion." << endl;
                cout << "           hand -- Describe all cards in your hand." << endl;
                cout << "           board -- Describe all cards on the board." << endl;
            }
            else if (cmd == "end") { //end turn
                activeP->trigger(otherP, EoT, -1, 0);
                activeP->bury();
                otherP->bury();
                turnno += 1;
                //end of the active player's turn
                swap(activeP, otherP);
                // start of the other player's turn
                activeP->MagicModify(1);
                activeP->CurMagicSet(1);
                activeP->draw(1);
                activeP->trigger(otherP, SoT, -1, 0);
                activeP->bury();
                otherP->bury();
            }
            else if (cmd == "quit") { //ends the game
                cout << "bye! ;(" << endl;
                break;
            }
            else if ((cmd == "draw")&&(isTesting)) { //draw a card
                cout << "draw" << endl;
                activeP->draw(1);
            }
            else if ((cmd == "discard")&&(isTesting)) { //discard a hand card
                cout << "discard" << endl;
                if (!(inpt>>num)) cin >> num;
                activeP->discard(num);
            }
            else if (cmd == "attack") { //minion attack
                int heads = activeP->getPop();
                if (inpt>>num) {
                    if (inpt>>num2) {
                        activeP->getBoard(num - 1)->attack(otherP->getBoard(num - 1));
                        activeP->bury();
                        otherP->bury();
                    } else {
                        activeP->getBoard(num - 1)->attack(otherP);
                    }
                } else {
                    cin >> num;
                    if (cin>>num2) {
                        activeP->getBoard(num - 1)->attack(otherP->getBoard(num - 1));
                        activeP->bury();
                        otherP->bury();
                    } else {
                        activeP->getBoard(num - 1)->attack(otherP);
                    }
                }
                if (activeP->getPop() > heads) {
                    int j = activeP->getPop() - heads;
                    for (int i =0; i < j; i++) {
                        activeP->trigger(otherP, M_out, -1, 0);
                    }
                }
            }
            else if (cmd == "play") { //play a card
                if (isTesting) activeP->CurMagicSet(100);
                if (!(inpt>>num)) {
                    cin >> num;
                    if (cin>>num2) {
                        Player* pp = (num2 == 1)? nullptr:otherP;
                        if ((cin>>aux)&&(aux == "r")) {
                            activeP->play(num, 6, pp);
                        } else {
                            cin >> num3;
                            activeP->play(num, num3, pp);
                        }
                    } else {
                        activeP->trigger(otherP, M_in, num, 1);
                        otherP->trigger(activeP, M_in, num, 2);
                        activeP->play(num);
                    }
                } else {
                    inpt >> num2;
                    Player* pp = (num2 == 1)? nullptr:otherP;
                    if ((inpt>>aux)&&(aux == "r")) {
                        activeP->play(num, 6, pp);
                    } else if (inpt >> num3){
                        activeP->play(num, num3, pp);
                    } else {
                        activeP->trigger(otherP, M_in, num, 1);
                        otherP->trigger(activeP, M_in, num, 2);
                        activeP->play(num);
                    }
                }
                if (isTesting) activeP->CurMagicSet(0);
                activeP->bury();
                otherP->bury();
            }
            else if (cmd == "use") { //minion ability
                cout << "use" << endl;
            }
            else if (cmd == "inspect") { //description of a card
                cout << "inspect" << endl;
            }
            else if (cmd == "hand") { // show hand
                cout << "hand" << endl;
            }
            else if (cmd == "board") { //show board
                cout << "board" << endl;
            }
            else {
                cout << "invalid command" << endl;
            }
        }
    }
    catch (ios::failure &) {
    }
}
